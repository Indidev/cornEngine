#include "TriangleFactory.h"

const int TriangleFactory::PIXELSIZE = 5;
const int TriangleFactory::THRESHOLD = 220;
const int TriangleFactory::NUM_EDGES = 30;
const char* TriangleFactory::TAG = "model/primitives/TriangleFactory";

const QString TriangleFactory::PNT = "points";
const QString TriangleFactory::TRI = "triangles";
const QString TriangleFactory::SQR = "squares";
const QString TriangleFactory::FAN = "fans";
const QString TriangleFactory::STRIP = "strips";
const QString TriangleFactory::CIRC = "circles";

QList<Triangle> TriangleFactory::fromImg(QImage &img, Point delta)
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
    Log::d(QString::fromUtf8(TAG), "Time taken: " + QString::number(millis) + "ms", "fromImg(QImage, Point)");

    return ts;
}

QList<Triangle> TriangleFactory::fromFile(QHash<QString, QString> fileContent)
{
    QList<Triangle> colModel;
    QHash<QString, Point> pointL;

    //Points
    QList<QString> elems = fileContent[PNT].split(",", QString::SkipEmptyParts);
    //add all points to point list
    for (QString &elem : elems) {
        QList<QString> params = elem.split("|");
        if (params.length() == 2) {
            pointL[params[0].trimmed()] = toPoint(params[1]);
        }
    }

    //Triangles
    QList<Point> p = getPoints(fileContent[TRI], pointL);
    //append triangles
    for (int i = 0; i < p.length() - 2; i += 3)
        colModel.append(Triangle(p[i], p[i + 1], p[i + 2]));

    //Fans
    p = getPoints(fileContent[FAN], pointL);
    //append triangles
    for (int i = 1; i < p.length() - 1; i++)
        colModel.append(Triangle(p[0], p[i], p[i + 1]));

    //Strips
    p = getPoints(fileContent[STRIP], pointL);
    //append triangles
    for (int i = 0; i < p.length() - 2; i++)
        colModel.append(Triangle(p[i], p[i + 1], p[i + 2]));

    //Squares
    p = getPoints(fileContent[SQR], pointL);
    //append squares
    for (int i = 0; i < p.length() - 2; i += 4) {
        colModel.append(Triangle(p[i], p[i + 1], p[i + 2]));
        colModel.append(Triangle(p[i + 2], p[i + 3], p[i]));
    }

    //circles
    elems = fileContent[CIRC].split(",", QString::SkipEmptyParts);
    //itterate over all circles
    for (QString elem: elems) {
        if (elem.contains("|")) {
            p.clear();
            QList<QString> splitted = elem.split("|", QString::SkipEmptyParts);
            p.append(toPoint(splitted[0]));
            int r = splitted[1].trimmed().toInt();
            p.append(p.front() + Point(0, r));
            //create all fan points
            for (int i = 0; i < NUM_EDGES; i++) {
                p.append(p.last().rotated(Math::degToRad(360 / NUM_EDGES), p.first()));
            }
            //add resulting fan to triangle list
            for (int i = 1; i < p.length() - 1; i++)
                colModel.append(Triangle(p[0], p[i], p[i + 1]));

        }
    }

    return colModel;
}

QImage TriangleFactory::toImg(QList<Triangle> &triangles, Point &offset)
{
    int w = 0, h = 0;

    offset = Point(0, 0);

    for (Triangle &t: triangles) {
        int r = t.getBB().right();
        int b = t.getBB().bottom();
        w = r > w? r : w;
        h = b > h? b : h;
        if (offset.x() > t.getBB().left())
            offset.setX(t.getBB().left());
        if (offset.y() > t.getBB().top())
            offset.setY(t.getBB().top());
    }

    QImage img(w - offset.x(), h - offset.y(), QImage::Format_ARGB32);
    img.fill(Qt::transparent);

    QPainter p(&img);

    for (Triangle t: triangles) {
        Point *points = t.getPoints();

        //p.fillRect(t.getBB(), Qt::black);
        for (int i = 0; i < 3; i++) {

            p.drawLine(points[i] - offset, points[(i + 1) % 3] - offset);
        }
    }

    p.end();

    return img;
}

QList<Triangle> TriangleFactory::square(int x, int y, Point delta)
{
    //transform pack into original image size
    x *= PIXELSIZE;
    y *= PIXELSIZE;

    //add delta;
    x += delta.x();
    y += delta.y();

    QList<Triangle> s;
    s.append(Triangle(Point(x, y), Point(x + PIXELSIZE, y), Point(x + PIXELSIZE, y + PIXELSIZE)));
    s.append(Triangle(Point(x, y), Point(x + PIXELSIZE, y + PIXELSIZE), Point(x, y + PIXELSIZE)));
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

Point TriangleFactory::toPoint(QString &input)
{
    QStringList splitted = input.split(".");
    if (splitted.size() == 2)
        return Point(splitted[0].trimmed().toInt(), splitted[1].trimmed().toInt());
    else
        return Point(0, 0);
}

QList<Point> TriangleFactory::getPoints(const QString &value, const QHash<QString, Point> &pointL)
{
    QList<Point> p;

    QList<QString> elems = value.split(",", QString::SkipEmptyParts);
    for (QString &elem : elems) {
        if (elem.contains("."))
            p.append(toPoint(elem));
        else
            p.append(pointL[elem.trimmed()]);
    }

    return p;
}


