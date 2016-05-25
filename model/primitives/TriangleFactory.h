#ifndef TRIANGLEFACTORY_H
#define TRIANGLEFACTORY_H

#include <QList>
#include <QImage>
#include <QRgb>
#include <QPainter>
#include <QTime>
#include <QString>

#include "model/primitives/Triangle.h"
#include "control/util/Log.h"

/**
 * @brief The TriangleFactory class provides methodes to creates triangle lists from primitives or images
 */
class TriangleFactory
{
public:

    /**
     * @brief creates a triangle list from a collision picture
     * @param img collision image, chould be black and white (black = collision, white = no collision)
     * @param delta optional delta for the triangles
     * @return triangle list from image
     */
    static QList<Triangle> fromImg(QImage &img, Point delta = Point());

    /**
     * @brief paint triangles onto an image
     * @param triangles put triangles in there...
     * @return imgage generated form triangle list
     */
    static QImage toImg(QList<Triangle> &triangles, Point &offset);

protected:
    static const int PIXELSIZE;
    static const int THRESHOLD;
    static const char* TAG;

    static QList<Triangle> square(int x, int y, Point delta);
    static QImage resizedEdged(QImage &img);
    static int value(int rgb);
};

#endif // TRIANGLEFACTORY_H
