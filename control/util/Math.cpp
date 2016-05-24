#include "Math.h"

float Math::degToRad(float degree)
{
    return degree / 360.f * _2PI;
}

float Math::radToDeg(float rad)
{
    return rad / _2PI * 360.f;
}
