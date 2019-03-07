#pragma once

#include "math/vec2.hpp"


class QMouseEvent;

class MouseEvent
{
  public:
    enum class Buttons
    {
        Left =   1 << 0,
        Middle = 1 << 1,
        Right =  1 << 2,
    };

    MouseEvent(QMouseEvent* event);

    vec2i position;
    Buttons buttons;
};

MouseEvent::Buttons& operator|=(MouseEvent::Buttons& lhs, MouseEvent::Buttons rhs);
bool operator&(MouseEvent::Buttons lhs, MouseEvent::Buttons rhs);
