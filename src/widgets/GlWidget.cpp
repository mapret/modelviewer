#include "gl_tools/GL.hpp" //Must be included before other OpenGL includes
#include "GlWidget.hpp"
#include "MouseEvent.hpp"
#include "Renderer.hpp"
#include "windows/MainWindow.hpp"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>


namespace
{
  QGLFormat getOpenglFormat()
  {
    QGLFormat format;
    format.setVersion(4, 2);
    format.setProfile(QGLFormat::CoreProfile);
    return format;
  }
}

GlWidget::GlWidget(MainWindow* main_window)
  : QGLWidget(getOpenglFormat()),
    main_window_(main_window),
    update_timer_(main_window)
{
  update_timer_.setInterval(1000 / 60);
  QObject::connect(&update_timer_, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

GlWidget::~GlWidget()
{
}

const Model& GlWidget::getModel() const
{
  return model_;
}

void GlWidget::initializeGL()
{
  QGLWidget::initializeGL();
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW");
  renderer_ = std::make_unique<Renderer>();

  auto arguments = QApplication::arguments();
  if (arguments.size() >= 2)
    emit loadFile(arguments[1]);
}

void GlWidget::onUpdate()
{
  std::chrono::duration<float> ts = Clock::now() - last_update_time_;
  last_update_time_ = Clock::now();
  renderer_->update(model_, transform_, ts.count());
  repaint();
}

void GlWidget::paintGL()
{
  QGLWidget::paintGL();
  renderer_->draw(model_, transform_, camera_);
}

void GlWidget::resizeGL(int w, int h)
{
  QGLWidget::resizeGL(w, h);
  glViewport(0, 0, w, h);
  camera_.setAspectRatio(static_cast<float>(w) / h);
}

void GlWidget::loadFile(QString path)
{
  if (!model_.import(path.toStdString()))
    throw std::runtime_error("Failed to import \"" + path.toStdString() + "\"");
  transform_.setNumberOfBones(model_.getBoneCount());
  last_update_time_ = Clock::now();
  emit fileLoaded();
}

void GlWidget::playAnimation(QString name)
{
  std::string animation_name = name.toStdString();
  size_t index = model_.getAnimationIndex(animation_name);
  transform_.setCurrentAnimationIndex(index);
  renderer_->update(model_, transform_, 0);
  startAnimation();
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

void GlWidget::resetAnimation()
{
  transform_.resetAnimation();
  renderer_->update(model_, transform_, 0);
  repaint();
}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
  camera_.mousePressEvent(MouseEvent(event));
}

void GlWidget::mouseMoveEvent(QMouseEvent* event)
{
  camera_.mouseMoveEvent(MouseEvent(event));
  repaint();
}

void GlWidget::wheelEvent(QWheelEvent* event)
{
  camera_.mouseWheelEvent(event->delta());
  repaint();
}
