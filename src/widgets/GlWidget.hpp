#pragma once

#include "BoneTransform.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include <chrono>
#include <memory>
#include <QtCore/QTimer>
#include <QtWidgets/QOpenGLWidget>


class MainWindow;
class Renderer;
using Clock = std::chrono::high_resolution_clock;

class GlWidget : public QOpenGLWidget
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
    void mouseDoubleClickEvent(QMouseEvent* event) override;

  private:
    MainWindow* main_window_;
    std::unique_ptr<Renderer> renderer_;
    Model model_;
    BoneTransform transform_;
    Camera camera_;
    QTimer update_timer_;
    Clock::time_point last_update_time_;
    std::vector<QWidget*> visible_dock_widgets_;
    float animation_speed_ = 1.f;

  public slots:
    void loadFile(QString path);
    void playAnimation(QString name);
    void startAnimation();
    void toggleAnimation();
    void setAnimationTime(float time);
    void resetAnimation();
    void setWireframeVisible(bool visible);
    void setAnimationSpeed(float animation_speed);
    void resetCamera();
    void resetCameraZoom();
    void onUpdate();

  signals:
    void fileLoaded(QString path);
    void fileLoadError(QString path, QString message);
    void animationChanged(QString name, float duration);
    void animationUpdated(float timestamp);
};
