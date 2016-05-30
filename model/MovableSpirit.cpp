#include "MovableSpirit.h"

MovableSpirit::MovableSpirit(Spirit *spirit)
{
    this->spirit = spirit;
    init();
}

MovableSpirit::MovableSpirit(QString name)
{
    this->spirit = SpiritManager::getSpirit(name);
    init();
}

void MovableSpirit::init()
{
    img = NULL;
    curAngle = 0.f;
    //center and vector center -> rotating point
    center = PointF(Point(spirit->getSize()));
    center /= 2;

    rotP = PointF(spirit->getPivot());
    movP = spirit->getroot();
    vecCP = rotP - center;

    //calculate bounding box
    int x = rotP.x() > center.x()? 0: spirit->getSize().width();
    int y = rotP.y() > center.y()? 0: spirit->getSize().height();
    int radius = rotP.distance(Point(x, y));
    bb = QRect(-radius, -radius, 2 * radius, 2 * radius);

    pos = -movP;
    (void) 4;
}

QImage *MovableSpirit::getCrop(const QRect &rect, long time, Point &offset)
{
    if (img)
        delete img;

    offset = pos - rect.topLeft(); //global offset

    img = new QImage(spirit->getFrame(time));

    //rotate image if necessary
    if (fabs(curAngle) > 0.0001) {
        //get center
        QTransform trans;
        trans.rotateRadians(curAngle);
        *img = img->transformed(trans, Qt::SmoothTransformation);

        //get new center
        PointF c(Point(img->size()));
        c /= 2;

        //rotate vector from new center to new rotation point
        PointF vecCPn(vecCP);
        vecCPn.rotate(curAngle);

        //add picture shift to offset
        offset += (rotP - c - vecCPn).toPoint();

        //remove after test
        //display col-model
        /*if (spirit->hasColModel()) {
            QPainter p(img);

            QRect r = getBB();
            QList<Triangle> ts = colModel(r);
            Point of;
            p.drawPoint(-(rotP - c - vecCPn));
            p.drawImage(-(rotP - c - vecCPn) + of, TriangleFactory::toImg(ts, of));
            p.end();
        }*/

    }
    return img;
}

bool MovableSpirit::isInScreen(const QRect &rect)
{
    return rect.intersects(bb);
}

void MovableSpirit::setPos(const Point &pos)
{
    bb.translate(pos - this->pos);
    this->pos = pos - movP;
}

void MovableSpirit::translate(const Point delta)
{
    bb.translate(delta);
    this->pos += delta;
}

void MovableSpirit::rotate(float angle, CE::Angle type, bool absolut)
{
    if (type == CE::DEG)
        angle = Math::degToRad(angle);

    curAngle = absolut? angle: curAngle + angle;
}

QList<Triangle> MovableSpirit::colModel(QRect &)
{
    QList<Triangle> colModel = spirit->getColModel();

    //rotate if necessary (todo: evaluate if faster to do this only when angle is set)
    if (fabs(curAngle) > 0.0001) {
        for (Triangle &t: colModel)
            t.rotate(curAngle, rotP.toPoint());
    }

    return colModel;
}

