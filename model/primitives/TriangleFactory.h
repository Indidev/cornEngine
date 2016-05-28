#ifndef TRIANGLEFACTORY_H
#define TRIANGLEFACTORY_H

#include <QList>
#include <QImage>
#include <QRgb>
#include <QPainter>
#include <QTime>
#include <QString>
#include <QHash>

#include "model/primitives/Triangle.h"
#include "model/primitives/Point.h"
#include "control/util/Log.h"
#include "control/util/Math.h"

/**
 * @brief The TriangleFactory class provides methodes to creates triangle lists from primitives or images
 */
class TriangleFactory
{
public:

    static const char* PNT;
    static const char* TRI;
    static const char* SQR;
    static const char* FAN;
    static const char* STRIP;
    static const char* CIRC;

    /**
     * @brief creates a triangle list from a collision picture
     * @param img collision image, chould be black and white (black = collision, white = no collision)
     * @param delta optional delta for the triangles
     * @return triangle list from image
     */
    static QList<Triangle> fromImg(QImage &img, Point delta = Point());

    /**
     * @brief create a triangle list from content of a collision model file
     * @param fileContent content from file
     * @return triangle list from file
     */
    static QList<Triangle> fromFile(QHash<QString, QString> &fileContent);

    /**
     * @brief paint triangles onto an image
     * @param triangles put triangles in there...
     * @return imgage generated form triangle list
     */
    static QImage toImg(QList<Triangle> &triangles, Point &offset);

protected:
    static const int PIXELSIZE;
    static const int THRESHOLD;
    static const int NUM_EDGES;
    static const char* TAG;

    static QList<Triangle> square(int x, int y, Point delta);
    static QImage resizedEdged(QImage &img);
    static int value(int rgb);
    static Point toPoint(QString &input);
    static QList<Point> getPoints(const QString &value, const QHash<QString, Point> &pointL);
};

#endif // TRIANGLEFACTORY_H
