#pragma once

#include "BoneTransform.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include <chrono>
#include <memory>
#include <QtCore/QTimer>
#include <QtOpenGL/QGLWidget>


class MainWindow;
class Renderer;
using Clock = std::chrono::high_resolution_clock;

class GlWidget : public QGLWidget
{
  Q_OBJECT

  public:
    GlWidget(MainWindow* main_window);
    ~GlWidget();

    const Model& getModel() const;

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
    BoneTransform transform_;
    Camera camera_;
    QTimer update_timer_;
    Clock::time_point last_update_time_;

  public slots:
    void loadFile(QString path);
    void playAnimation(QString name);
    void startAnimation();
    void toggleAnimation();
    void resetAnimation();
    void onUpdate();

  signals:
    void fileLoaded();
};
