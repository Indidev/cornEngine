#include "Triangle.h"

Triangle::Triangle()
{
    points = new Point[3];
    init();
}

Triangle::Triangle(Point points[]) {
    this->points = new Point[3];
    for (int i = 0; i < 3; i++)
        this->points[i] = points[i];
    init();
}

Triangle::Triangle(Point p1, Point p2, Point p3) {
    points = new Point[3];
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    init();
}

Triangle::Triangle(const Triangle &other)
{
    points = new Point[3];
    for (int i = 0; i < 3; i++)
        points[i] = other.points[i];
    init();
}

Triangle::~Triangle()
{
    delete points;
}

void Triangle::init()
{
    vecAB = points[1] - points[0];
    vecAC = points[2] - points[0];
    vecBC = points[2] - points[1];
}

void Triangle::translate(const Point &delta)
{
    for (int i = 0; i < 3; i++)
        points[i] += delta;
}

Triangle Triangle::translated(const Point &delta)
{
    Triangle t(*this);
    t.translate(delta);
    return t;
}

void Triangle::rotate(const float radAngle, Point rotPoint, CE::Angle type)
{
    //translate to root
    //translate(-rotPoint);

    //rotate every point
    for (int i = 0; i < 3; i++) {
        points[i].rotate(radAngle, rotPoint, type);
        //rotate (todo: change to other data structure (e.g. extend Point and implement rotate function there)
        //points[i] = Point(cos(radAngle) * (float) points[i].x() - sin(radAngle) * (float) points[i].y(),
        //                   sin(radAngle) * (float) points[i].x() + cos(radAngle) * (float) points[i].y());
    }

    //translate back
    //translate(rotPoint);
    init();
}

Triangle Triangle::rotated(const float radAngle, Point rotPoint, CE::Angle type)
{
    Triangle t(*this);
    t.rotate(radAngle, rotPoint, type);
    return t;
}

bool Triangle::intersects(Triangle &other)
{
    //check if triangles are in each other
    if (isIn(other) || other.isIn(*this)) {
        return true;
    }

    //check if lines are intersecting
    Triangle::Vec tVecs[] = {Triangle::Vec{points[0], vecAB},
                             Triangle::Vec{points[0], vecAC},
                             Triangle::Vec{points[1], vecBC}};
    Triangle::Vec oVecs[] = {Triangle::Vec{other.points[0], other.vecAB},
                             Triangle::Vec{other.points[0], other.vecAC},
                             Triangle::Vec{other.points[1], other.vecBC}};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (intersects(tVecs[i], oVecs[j]))
                return true;
    return false;
}

bool Triangle::intersects(Vec &v1, Vec &v2)
{
    // check if vectores are parallel
    if ((float) Point::dotProduct(v1.vec, v2.vec) / (v1.vec.distance() * v2.vec.distance()) > 0.999) {
        return isOnVec(v1, v2.org) || isOnVec(v1, v2.org + v2.vec) || isOnVec(v2, v1.org);
    }

    //calculate intersection of vectors
    float u = (float) (v2.org.x() + v1.org.y() * v2.vec.x() - v2.org.y() + v2.vec.x() - v1.org.x() * v2.vec.y())
            / (float) (v1.vec.x() * v2.vec.y() - v2.vec.x() * v1.vec.y());

    float v = ((float) v1.org.y() + u * (float) v1.vec.y() - (float) v2.org.y()) / (float) v2.vec.y();

    return (u >= 0) && (u <= 1) && (v >= 0) && (v <= 1);
}

bool Triangle::isIn(Point &p)
{
    // Compute vectors
    Point vecAP = p - points[0];

    //copute v
    float v = (float) (vecAB.x() * vecAP.y() - vecAP.x() * vecAB.y())
            / (float) (vecAB.x() * vecAC.y() - vecAC.x() * vecAB.y());

    float u = ((float) vecAP.x() - v * (float) vecAC.x()) / (float) vecAB.x();
    // Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool Triangle::isIn(Triangle &t)
{
    for (int i = 0; i < 3; i++)
        if (!isIn(t.points[i]))
            return false;

    return true;
}

QRect Triangle::getBB()
{
    int minX = min(points[0].x(), min(points[1].x(), points[2].x()));
    int maxX = max(points[0].x(), max(points[1].x(), points[2].x()));
    int minY = min(points[0].y(), min(points[1].y(), points[2].y()));
    int maxY = max(points[0].y(), max(points[1].y(), points[2].y()));

    return QRect(Point(minX, minY), Point(maxX, maxY));
}

Point *Triangle::getPoints()
{
    return points;
}

Triangle &Triangle::operator=(const Triangle other)
{

    for (int i = 0; i < 3; i++)
        points[i] = other.points[i];
    init();
    return *this;
}

bool Triangle::operator==(const Triangle &other)
{
    for (int i = 0; i < 3; i++)
        if (points[i].x() != other.points[i].x() || points[i].y() != other.points[i].y())
            return false;
    return true;
}

bool Triangle::isOnVec(Triangle::Vec &vec, Point p)
{
    Point end = vec.org + vec.vec;

    return fabs(vec.vec.distance() - ((p - vec.org).distance() + (end - p).distance())) < 0.0001;
}

int Triangle::min(int a, int b)
{
    return a < b? a: b;
}

int Triangle::max(int a, int b)
{
    return a > b? a: b;
}
