#pragma once

#include "Camera.hpp"
#include "Model.hpp"
#include <memory>
#include <QtOpenGL/QGLWidget>


class MainWindow;
class Renderer;

class GlWidget : public QGLWidget
{
  Q_OBJECT

  public:
    GlWidget(MainWindow* main_window);
    ~GlWidget();

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

  private:
    MainWindow* main_window_;
    std::unique_ptr<Renderer> renderer_;
    Model model_;
    Camera camera_;

  public slots:
    void loadFile(QString path);
};
