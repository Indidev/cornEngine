#include "PointF.h"

PointF::PointF()
{
    mX = 0.f;
    mY = 0.f;
}

PointF::PointF(float xVar, float yVar)
{
    mX = xVar;
    mY = yVar;
}

PointF::PointF(const QPoint &p)
{
    mX = p.x();
    mY = p.y();
}

PointF::PointF(const PointF &p)
{
    mX = p.x();
    mY = p.y();
}

PointF::PointF(const PointF *p)
{
    mX = p->x();
    mY = p->y();
}

float PointF::x() const
{
    return mX;
}

float PointF::y() const
{
    return mY;
}

void PointF::setX(float xVar)
{
    mX = xVar;
}

void PointF::setY(float yVar)
{
    mY = yVar;
}

Point PointF::toPoint()
{
    return Point (mX + 0.5, mY + 0.5);
}

void PointF::rotate(float angle, PointF rotP, CE::Angle type)
{
    //translate to root
    operator -=(rotP);

    if (type == CE::DEG)
        angle = Math::degToRad(angle);

    float oldX = mX;
    float oldY = mY;

    mX = cos(angle) * oldX - sin(angle) * oldY;
    mY = sin(angle) * oldX + cos(angle) * oldY;

    //translate back
    operator +=(rotP);
}

PointF PointF::rotated(float angle, PointF rotP, CE::Angle type)
{
    PointF r(this);
    r.rotate(angle, rotP, type);
    return r;
}

float PointF::distance(const QPoint other)
{
    return sqrt((x() - other.x()) * (x() - other.x()) + (y() - other.y()) * (y() - other.y()));
}

float PointF::distance(const PointF other)
{
    return sqrt((x() - other.x()) * (x() - other.x()) + (y() - other.y()) * (y() - other.y()));
}

PointF PointF::operator -(const PointF &other)
{
    return PointF(mX - other.mX, mY - other.mY);
}

PointF PointF::operator -()
{
    return PointF(-mX, -mY);
}

PointF PointF::operator +(const PointF &other)
{
    return PointF(mX + other.mX, mY + other.mY);
}

PointF PointF::operator /(float div)
{
    return PointF(mX / div, mY / div);
}

PointF PointF::operator *(float fac)
{
    return PointF(mX * fac, mY * fac);
}

void PointF::operator -=(const PointF &other)
{
    mX -= other.mX;
    mY -= other.mY;
}

void PointF::operator +=(const PointF &other)
{
    mX += other.mX;
    mY += other.mY;
}

void PointF::operator /=(float div)
{
    mX /= div;
    mY /= div;
}

void PointF::operator *=(float fac)
{
    mX *= fac;
    mY *= fac;
}

bool PointF::operator==(const PointF &other)
{
    return same(mX, other.mX) && same(mY, other.mY);
}

PointF &PointF::operator=(const PointF &other)
{
    mX = other.x();
    mY = other.y();
    return *this;
}

bool PointF::same(float a, float b)
{
    return fabs(a - b) < 0.00001;
}
