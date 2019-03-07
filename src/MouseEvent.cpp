#include "MouseEvent.hpp"
#include <QtGui/QMouseEvent>


using Buttons = MouseEvent::Buttons;

MouseEvent::MouseEvent(QMouseEvent* event)
{
  position = vec2i(event->x(), event->y());
  buttons = static_cast<Buttons>(0);
  auto b = event->buttons();
  if (b & Qt::MouseButton::LeftButton)   buttons |= Buttons::Left;
  if (b & Qt::MouseButton::MiddleButton) buttons |= Buttons::Middle;
  if (b & Qt::MouseButton::RightButton)  buttons |= Buttons::Right;
}

Buttons& operator|=(Buttons& lhs, Buttons rhs)
{
  lhs = static_cast<Buttons>(static_cast<int>(lhs) | static_cast<int>(rhs));
  return lhs;
}

bool operator&(Buttons lhs, Buttons rhs)
{
  return (static_cast<int>(lhs) & static_cast<int>(rhs)) != 0;
}
