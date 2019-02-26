#include "widgets/GlWidget.hpp"
#include "MainWindow.hpp"
#include "ui/mainwindow.ui.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);

  //Replace placeholder button by GlWidget
  auto* gl_widget_ = new GlWidget(this);
  ui_->layout_gl->replaceWidget(ui_->gl_placeholder, gl_widget_);
  ui_->gl_placeholder->deleteLater();
}

MainWindow::~MainWindow()
{
}
