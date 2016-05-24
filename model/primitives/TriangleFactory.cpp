#include "TriangleFactory.h"

const int TriangleFactory::PIXELSIZE = 5;
const int TriangleFactory::THRESHOLD = 220;
const char* TriangleFactory::TAG = "model/primitives/TriangleFactory";

QList<Triangle> TriangleFactory::fromImg(QImage &img, QPoint delta)
{
    QTime begin = QTime::currentTime();
    QList<Triangle> ts;
    QImage workImg = resizedEdged(img);

    for (int x = 0; x < workImg.width(); x++) {
        for (int y = 0; y < workImg.height(); y++) {
            if (QColor::fromRgb(workImg.pixel(x, y)).value() < THRESHOLD) {
                ts.append(square(x, y, delta));
            }
        }
    }
    long millis = begin.msecsTo(QTime::currentTime());
    Log::d(QString::fromUtf8(TAG), "Time taken: " + QString::number(millis) + "ms", "fromImg(QImage, QPoint)");

    return ts;
}

QImage TriangleFactory::toImg(QList<Triangle> &triangles)
{
    int w = 0, h = 0;

    for (Triangle &t: triangles) {
        int r = t.getBB().right();
        int b = t.getBB().bottom();
        w = r > w? r : w;
        h = b > h? b : h;
    }

    QImage img(w, h, QImage::Format_ARGB32);
    img.fill(Qt::transparent);

    QPainter p(&img);

    for (Triangle t: triangles) {
        QPoint *points = t.getPoints();

        //p.fillRect(t.getBB(), Qt::black);
        for (int i = 0; i < 3; i++) {

            p.drawLine(points[i], points[(i + 1) % 3]);
        }
    }

    p.end();

    return img;
}

QList<Triangle> TriangleFactory::square(int x, int y, QPoint delta)
{
    //transform pack into original image size
    x *= PIXELSIZE;
    y *= PIXELSIZE;

    //add delta;
    x += delta.x();
    y += delta.y();

    QList<Triangle> s;
    s.append(Triangle(QPoint(x, y), QPoint(x + PIXELSIZE, y), QPoint(x + PIXELSIZE, y + PIXELSIZE)));
    s.append(Triangle(QPoint(x, y), QPoint(x + PIXELSIZE, y + PIXELSIZE), QPoint(x, y + PIXELSIZE)));
    return s;
}

QImage TriangleFactory::resizedEdged(QImage &img)
{
    QImage resized = img.scaledToWidth((img.width() + PIXELSIZE / 2) / PIXELSIZE, Qt::SmoothTransformation);

    QImage edged(resized);
    for (int x = 1; x < edged.width() - 1; x++) {
        for (int y = 1; y < edged.height() - 1; y++) {
            int v = value(resized.pixel(x, y));

            if (v < THRESHOLD) {
                if (!(value(resized.pixel(x , y - 1)) >= THRESHOLD || value(resized.pixel(x - 1, y)) >= THRESHOLD ||
                        value(resized.pixel(x, y + 1)) >= THRESHOLD || value(resized.pixel(x + 1, y)) >= THRESHOLD))
                        edged.setPixel(x, y, 0xFFFFFF);
            }
        }
    }

    return edged;
}

int TriangleFactory::value(int rgb)
{
    return QColor::fromRgb(rgb).value();
}


