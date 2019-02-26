#pragma once

#include <QtOpenGL/QGLWidget>


class MainWindow;

class GlWidget : public QGLWidget
{
  Q_OBJECT

  public:
    GlWidget(MainWindow* main_window);

  private:
    MainWindow* main_window_;
};
