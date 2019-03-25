#include "widgets/GlWidget.hpp"
#include "MainWindow.hpp"
#include "ui/mainwindow.ui.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);

  //Replace placeholder button by GlWidget
  gl_widget_ = new GlWidget(this);
  ui_->layout_gl->replaceWidget(ui_->gl_placeholder, gl_widget_);
  ui_->gl_placeholder->deleteLater();

  QObject::connect(gl_widget_, SIGNAL(fileLoaded()), this, SLOT(fileLoaded()));
  QObject::connect(ui_->chk_wireframe, SIGNAL(toggled(bool)), this, SLOT(setWireframeVisible(bool)));
  QObject::connect(ui_->btn_reset_camera, SIGNAL(pressed()), this, SLOT(resetCamera()));
  QObject::connect(ui_->btn_reset_zoom, SIGNAL(pressed()), this, SLOT(resetCameraZoom()));
  QObject::connect(ui_->lst_animations, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(startAnimation(QListWidgetItem*)));
  QObject::connect(ui_->btn_toggle_play, SIGNAL(pressed()), this, SLOT(toggleAnimation()));
  QObject::connect(ui_->btn_reset, SIGNAL(pressed()), this, SLOT(resetAnimation()));
  QObject::connect(ui_->spn_animation_speed, SIGNAL(valueChanged(double)), this, SLOT(setAnimationSpeed(double)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::fileLoaded()
{
  const auto& model = gl_widget_->getModel();
  ui_->lst_animations->clear();
  for (const auto& animation_name : model.getAnimationNames())
    ui_->lst_animations->addItem(QString::fromStdString(animation_name));
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
