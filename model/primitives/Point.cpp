#include "Point.h"

void Point::rotate(float angle, QPoint rotP)
{
    //translate to root
    operator -=(rotP);

    float oldX = x();
    float oldY = y();

    setX(cos(angle) * oldX - sin(angle) * oldY);
    setY(sin(angle) * oldX + cos(angle) * oldY);

    //translate back
    operator +=(rotP);
}

Point Point::rotated(float angle, QPoint rotP)
{
    Point r(*this);
    r.rotate(angle, rotP);
    return r;
}

float Point::distance(QPoint other)
{
    return sqrt((x() - other.x()) * (x() - other.x()) + (y() - other.y()) * (y() - other.y()));
}

Point Point::operator -(const QPoint &other)
{
    return Point(this->x() - other.x(), this->y() - other.y());
}

Point Point::operator +(const QPoint &other)
{
    return Point(this->x() + other.x(), this->y() + other.y());
}
