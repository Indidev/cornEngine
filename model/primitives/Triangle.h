#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QLine>
#include <QString>
#include <QRect>

#include <math.h>

#include "model/primitives/Point.h"
#include "model/Types.h"

using std::cos;
using std::sin;

/**
 * @brief Represents a triangle, consisting of three points,
 * which should be given in clockwise order
 */
class Triangle
{
public:
    /**
     * @brief struct of a vector including an origin
     */
    struct Vec {
        Point org;
        Point vec;
    };

    /**
     * @brief creates a new triangle (all Points are 0)
     */
    Triangle();

    /**
     * @brief creates a new triangle from three points
     * @param points array of 3 points
     */
    Triangle(Point points[3]);

    /**
     * @brief creates a new triangle from three points
     * @param p1 point 1
     * @param p2 point 2
     * @param p3 point 3
     */
    Triangle(Point p1, Point p2, Point p3);

    /**
     * @brief creates a new triangle from another one
     * @param other other triangle
     */
    Triangle(const Triangle &other);

    ~Triangle();

    /**
     * @brief translates this triangle by a delta
     * @param delta delta to translate
     */
    void translate(const Point &delta);

    /**
     * @brief gives a translated copy of this triangle
     * @param delta vector to translate
     * @return translated copy
     */
    Triangle translated(const Point &delta);

    /**
     * @brief rotates the triangle clockwise around a given point
     * @param radAngle angle in radian
     * @param rotPoint point to rotate around (standart = 0|0)
     * @param type angle mode (default: CE::RAD)
     */
    void rotate(const float radAngle, Point rotPoint = Point(), CE::Angle type = CE::RAD);

    /**
     * @brief create a clockwise rotated copy
     * @param radAngle angle to rotate
     * @param rotPoint point to rotate around
     * @param type angle mode (default: CE::RAD)
     * @return rotated copy
     */
    Triangle rotated(const float radAngle, Point rotPoint = Point(), CE::Angle type = CE::RAD);

    /**
     * @brief check if another triangle intersects this one, including complete subsets
     * @param other triangle to check
     * @return whether triangle "other" is intersecting this or not
     */
    bool intersects(Triangle &other);

    /**
     * @brief computes whether a point is in the triangle or not.
     * Uses Barycentric coordinate system
     * @param p point to check
     * @return true if p is in the triangle
     */
    bool isIn(Point &p);

    /**
     * @brief computes whether a triangle is entirely inside this triangle
     * @param t triangle to check
     * @return true if t is in this triangle
     */
    bool isIn(Triangle &t);

    /**
     * @brief get the bounding box of this triangle
     * @return bounding box
     */
    QRect getBB();

    /**
     * @brief return the triangle's points
     * @return 3 points
     */
    Point *getPoints();

    Triangle& operator=(const Triangle other);
    bool operator==(const Triangle& other);

protected:
    Point *points;
    Point vecAB;
    Point vecAC;
    Point vecBC;

    bool intersects(Vec &v1, Vec &v2);
    bool isOnVec(Vec &vec, Point p);
    int min(int a, int b);
    int max(int a, int b);

private:
    void init();
};

#endif // TRIANGLE_H
