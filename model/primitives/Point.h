#ifndef POINT_H
#define POINT_H

#include <QPoint>
#include <QSize>

#include <math.h>

using std::cos;
using std::sin;

/**
 * @brief extends QPoint with mathematic methods
 */
class Point : public QPoint
{

public:
    /**
     * @brief creates an empty point(0, 0)
     */
    Point() {}

    /**
     * @brief creates a point from a QPoint
     * @param p
     */
    Point(QPoint p):QPoint(p) {}

    /**
     * @brief creates a point from x, y
     * @param x x-coordinate
     * @param y y-coordinate
     */
    Point(int x, int y):QPoint(x, y) {}

    /**
     * @brief creates a Point form a QSize [Point(QSize.width, QSize.height)]
     * @param s QSize to create point from
     */
    Point(QSize s):QPoint(s.width(), s.height()) {}

    /**
     * @brief rotate the point around a point clockwise for a given angle
     * @param angle angle to rotate in radian
     * @param rotP point to rotate around [default: (0|0)]
     */
    void rotate(float angle, QPoint rotP = QPoint());

    /**
     * @brief calculates the direct distance to another point, or length if used as vector
     * @param other point to calculate distance to, or Point(0, 0) if non is given
     * @return direct distance, or length without parameter
     */
    float distance(QPoint other = QPoint());

    Point operator -(const QPoint &other);
    Point operator +(const QPoint &other);
};

#endif // POINT_H
