#include "gl_tools/GL.hpp" //Must be included before other OpenGL includes
#include "GlWidget.hpp"
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
    main_window_(main_window)
{
}

GlWidget::~GlWidget()
{
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

void GlWidget::paintGL()
{
  QGLWidget::paintGL();
  renderer_->draw(model_, camera_);
}

void GlWidget::resizeGL(int w, int h)
{
  QGLWidget::resizeGL(w, h);
  glViewport(0, 0, w, h);
  camera_.setAspectRatio(static_cast<float>(w) / h);
}

void GlWidget::loadFile(QString path)
{
  model_.import(path.toStdString());
}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
  if (event->buttons() == Qt::MouseButton::LeftButton)
    camera_.mousePressEvent(vec2i(event->x(), event->y()));
}

void GlWidget::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() == Qt::MouseButton::LeftButton)
  {
    camera_.mouseMoveEvent(vec2i(event->x(), event->y()));
    repaint();
  }
}

void GlWidget::wheelEvent(QWheelEvent* event)
{
  camera_.mouseWheelEvent(event->delta());
  repaint();
}
