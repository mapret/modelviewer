#include "gl_tools/GL.hpp" //Must be included before other OpenGL includes
#include "GlWidget.hpp"
#include "ModelImporter.hpp"
#include "MouseEvent.hpp"
#include "Renderer.hpp"
#include "windows/MainWindow.hpp"
#include <array>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>


namespace
{
  QSurfaceFormat getOpenglFormat()
  {
    QSurfaceFormat format;
    format.setVersion(4, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    return format;
  }
}

GlWidget::GlWidget(MainWindow* main_window)
  : QOpenGLWidget(main_window),
    main_window_(main_window),
    update_timer_(main_window)
{
  setFormat(getOpenglFormat());
  update_timer_.setInterval(1000 / 60);
  QObject::connect(&update_timer_, &QTimer::timeout, this, &GlWidget::onUpdate);
}

GlWidget::~GlWidget()
{
  //Crashes on Windows if not called (because destruction is done by another thread than creation?)
  makeCurrent();
}

const Model& GlWidget::getModel() const
{
  return model_;
}

void GlWidget::initializeGL()
{
  QOpenGLWidget::initializeGL();
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW");
  renderer_ = std::make_unique<Renderer>();
  camera_.setWindowSize(vec2u(width(), height()));

  auto arguments = QApplication::arguments();
  if (arguments.size() >= 2)
    emit loadFile(arguments[1]);
}

void GlWidget::onUpdate()
{
  std::chrono::duration<float> ts = Clock::now() - last_update_time_;
  last_update_time_ = Clock::now();
  renderer_->update(model_, transform_, ts.count() * animation_speed_);
  repaint();
  emit animationUpdated(transform_.getAnimationTime());
}

void GlWidget::paintGL()
{
  QOpenGLWidget::paintGL();
  renderer_->draw(model_, transform_, camera_);
}

void GlWidget::resizeGL(int w, int h)
{
  QOpenGLWidget::resizeGL(w, h);
  glViewport(0, 0, w, h);
  camera_.setWindowSize(vec2u(w, h));
}

void GlWidget::loadFile(QString path)
{
  makeCurrent(); //Crashes on Windows if called via File->Open (because the function is not called by the main thread?)
  Model new_model;
  ModelImporter importer;
  if (!importer.import(path.toStdString(), new_model))
  {
    emit fileLoadError(path, QString::fromStdString(importer.getErrorMessage()));
    return;
  }
  model_ = std::move(new_model);
  transform_.setNumberOfBones(model_.getBoneCount());
  last_update_time_ = Clock::now();
  resetCameraZoom();
  emit fileLoaded(path);
}

void GlWidget::playAnimation(QString name)
{
  std::string animation_name = name.toStdString();
  size_t index = model_.getAnimationIndex(animation_name);
  transform_.setCurrentAnimationIndex(index);
  renderer_->update(model_, transform_, 0);
  startAnimation();
  emit animationChanged(name, model_.getAnimation(index).duration);
}

void GlWidget::startAnimation()
{
  transform_.setRunning(true);
  last_update_time_ = Clock::now();
  update_timer_.start();
}

void GlWidget::toggleAnimation()
{
  transform_.setRunning(!transform_.getRunning());
  if (!transform_.getRunning())
    update_timer_.stop();
  else
    startAnimation();
}

void GlWidget::setAnimationTime(float time)
{
  transform_.setAnimationTime(time);
  renderer_->update(model_, transform_, 0);
  repaint();
}

void GlWidget::resetAnimation()
{
  transform_.resetAnimation();
  renderer_->update(model_, transform_, 0);
  repaint();
}

void GlWidget::setWireframeVisible(bool visible)
{
  renderer_->setWireframe(visible);
  repaint();
}

void GlWidget::setAnimationSpeed(float animation_speed)
{
  animation_speed_ = animation_speed;
}

void GlWidget::resetCamera()
{
  camera_.reset();
  resetCameraZoom();
}

void GlWidget::resetCameraZoom()
{
  auto planes = camera_.getFrustumSidePlanes();
  vec3 min(std::numeric_limits<float>::max()); //Min and max of bounding box
  vec3 max(std::numeric_limits<float>::lowest());
  model_.forEachTriangle(model_.getTransformMatrices(transform_), [&](const vec3& p1, const vec3& p2, const vec3& p3)
  {
    for (auto& plane : planes)
    {
      if (plane.signedDistance(p1) > 0) plane.setDistanceFromOrigin(p1);
      if (plane.signedDistance(p2) > 0) plane.setDistanceFromOrigin(p2);
      if (plane.signedDistance(p3) > 0) plane.setDistanceFromOrigin(p3);
    }
    min = vec3::min(min, p1);
    min = vec3::min(min, p2);
    min = vec3::min(min, p3);
    max = vec3::max(max, p1);
    max = vec3::max(max, p2);
    max = vec3::max(max, p3);
  });
  camera_.setFrustumSidePlanes(planes, (min + max) / 2.f);
  repaint();
}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
  MouseEvent e(event);
  camera_.mousePressEvent(e);
  if (e.buttons & MouseEvent::Buttons::Middle)
  {
    vec3 ray_dir = camera_.getRayDirectionFromScreenPosition(e.position);
    float t = model_.intersectRay(camera_.getPosition(), ray_dir, transform_);
    if (t != std::numeric_limits<float>::infinity())
      camera_.setLastClickedPosition(camera_.getPosition() + ray_dir * t);
  }
}

void GlWidget::mouseMoveEvent(QMouseEvent* event)
{
  camera_.mouseMoveEvent(MouseEvent(event));
  if (!update_timer_.isActive())
    repaint();
}

void GlWidget::wheelEvent(QWheelEvent* event)
{
  camera_.mouseWheelEvent(event->delta());
  repaint();
}

void GlWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
  if (visible_dock_widgets_.empty())
  {
    for (auto* widget : main_window_->topLevelWidget()->findChildren<QDockWidget*>())
      if (widget->isVisible())
      {
        visible_dock_widgets_.push_back(widget);
        widget->hide();
      }
  }
  else
  {
    for (auto* widget : visible_dock_widgets_)
      widget->show();
    visible_dock_widgets_.clear();
  }
}
