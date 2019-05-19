#include "Globals.hpp"
#include "MainWindow.hpp"
#include "ui/mainwindow.ui.h"
#include "widgets/GlWidget.hpp"
#include "windows/AboutDialog.hpp"
#include "windows/ControlsDialog.hpp"
#include "windows/LicenseDialog.hpp"
#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);
  setWindowTitle(qglobals::APPLICATION_NAME);
  ui_->act_about->setText("About " + qglobals::APPLICATION_NAME);

  //Replace placeholder button by GlWidget
  gl_widget_ = new GlWidget(this);
  ui_->layout_gl->replaceWidget(ui_->gl_placeholder, gl_widget_);
  ui_->gl_placeholder->deleteLater();

  QSettings settings;
  restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
  restoreState(settings.value("mainWindowState").toByteArray());

  for (const auto& style : styles_.getNames())
  {
    QAction* action = new QAction(QString::fromStdString(style), ui_->menu_style);
    ui_->menu_style->addAction(action);
    QObject::connect(action, &QAction::triggered, this, [=](){
      styles_.setStyle(style);
    });
  }

  QObject::connect(gl_widget_, SIGNAL(fileLoaded(QString)), this, SLOT(fileLoaded(QString)));
  QObject::connect(ui_->chk_wireframe, SIGNAL(toggled(bool)), this, SLOT(setWireframeVisible(bool)));
  QObject::connect(ui_->btn_reset_camera, SIGNAL(pressed()), this, SLOT(resetCamera()));
  QObject::connect(ui_->btn_reset_zoom, SIGNAL(pressed()), this, SLOT(resetCameraZoom()));
  QObject::connect(ui_->lst_animations, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(startAnimation(QListWidgetItem*)));
  QObject::connect(ui_->btn_toggle_play, SIGNAL(pressed()), this, SLOT(toggleAnimation()));
  QObject::connect(ui_->btn_reset, SIGNAL(pressed()), this, SLOT(resetAnimation()));
  QObject::connect(ui_->spn_animation_speed, SIGNAL(valueChanged(double)), this, SLOT(setAnimationSpeed(double)));
  QObject::connect(ui_->act_open, SIGNAL(triggered(bool)), this, SLOT(openFileModal()));
  QObject::connect(ui_->act_exit, SIGNAL(triggered(bool)), this, SLOT(exitAction()));
  QObject::connect(ui_->act_controls, SIGNAL(triggered(bool)), this, SLOT(showControls()));
  QObject::connect(ui_->act_licenses, SIGNAL(triggered(bool)), this, SLOT(showLicenses()));
  QObject::connect(ui_->act_about, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
  QObject::connect(ui_->act_aboutqt, SIGNAL(triggered(bool)), this, SLOT(showAboutQt()));
}

MainWindow::~MainWindow()
{
}


void MainWindow::closeEvent(QCloseEvent* event)
{
  QSettings settings;
  settings.setValue("mainWindowGeometry", saveGeometry());
  settings.setValue("mainWindowState", saveState());

  QWidget::closeEvent(event);
}

void MainWindow::openFileModal()
{
  auto path = QFileDialog::getOpenFileName(this, "Select a model file");
  if (!path.isNull())
    emit gl_widget_->loadFile(path);
}

void MainWindow::exitAction()
{
  QApplication::closeAllWindows();
}

void MainWindow::fileLoaded(QString path)
{
  QFileInfo fileinfo(path);
  setWindowTitle(fileinfo.fileName() + " - " + qglobals::APPLICATION_NAME);
  const auto& model = gl_widget_->getModel();
  ui_->lst_animations->clear();
  for (const auto& animation_name : model.getAnimationNames())
    ui_->lst_animations->addItem(QString::fromStdString(animation_name));
}

void MainWindow::fileLoadError(QString path, QString message)
{
  QFileInfo fileinfo(path);
  QString filename = fileinfo.fileName();
  QMessageBox::critical(this, "Failed to open \"" + filename + "\"", "The file \"" + filename + "\" could not be opened.\n\n" + message);
}

void MainWindow::setWireframeVisible(bool value)
{
  emit gl_widget_->setWireframeVisible(value);
}

void MainWindow::resetCamera()
{
  emit gl_widget_->resetCamera();
}

void MainWindow::resetCameraZoom()
{
  emit gl_widget_->resetCameraZoom();
}

void MainWindow::startAnimation(QListWidgetItem* item)
{
  auto animation_name = item->text();
  emit gl_widget_->playAnimation(animation_name);
}

void MainWindow::toggleAnimation()
{
  emit gl_widget_->toggleAnimation();
}

void MainWindow::resetAnimation()
{
  emit gl_widget_->resetAnimation();
}

void MainWindow::setAnimationSpeed(double value)
{
  emit gl_widget_->setAnimationSpeed(static_cast<float>(value));
}

void MainWindow::showControls()
{
  ControlsDialog(this).exec();
}

void MainWindow::showLicenses()
{
  LicenseDialog(this).exec();
}

void MainWindow::showAbout()
{
  AboutDialog(this).exec();
}

void MainWindow::showAboutQt()
{
  QMessageBox::aboutQt(this, "About Qt - " + qglobals::APPLICATION_NAME);
}
