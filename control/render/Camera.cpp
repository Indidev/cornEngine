#include "Camera.h"

Camera::Camera(DrawableStack *stack, QSize boundary, QSize viewPort)
{
    this->stack = stack;
    this->boundary = boundary;
    this->viewPort = viewPort;
    this->position = QPoint(0, 0);
}

void Camera::setPosition(QPoint pos)
{
    if (pos.x() + viewPort.width() > boundary.width())
        pos.setX(boundary.width() - viewPort.width());
    if (pos.y() + viewPort.height() > boundary.height())
        pos.setY(boundary.height() - viewPort.height());

    if (pos.x() < 0)
        pos.setX(0);
    if (pos.y() < 0)
        pos.setY(0);
    position = pos;
}

const QPoint &Camera::getPosition()
{
    return position;
}

void Camera::setViewPort(QSize size)
{
    viewPort = size;
}

QImage *Camera::render(long time)
{
    return stack->render(QRect(position, viewPort), time);
}
