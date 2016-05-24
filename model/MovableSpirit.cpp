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
    center = Point(spirit->getSize()) / 2;
    rotP = center;
    vecCP = rotP - center;

    //calculate bounding box
    int x = rotP.x() < center.x()? 0: spirit->getSize().width();
    int y = rotP.y() < center.y()? 0: spirit->getSize().height();
    int radius = rotP.distance(Point(x, y));
    bb = QRect(rotP.x() - radius, rotP.y() - radius, 2 * radius, 2 * radius);
    bb.translate(pos);
}

QImage *MovableSpirit::getCrop(const QRect &rect, long time, QPoint &offset)
{
    if (img)
        delete img;

    offset = pos - rect.topLeft(); //global offset

    img = new QImage(spirit->getFrame(time));

    curAngle = (float) time / 300.;

    //rotate image if necessary
    if (fabs(curAngle) > 0.1) {
        //get center
        QTransform trans;
        trans.rotateRadians(curAngle);
        *img = img->transformed(trans);

        //get new center
        Point c = Point(img->size()) / 2;

        //rotate vector from new center to new point
        Point vecCPn(vecCP);
        vecCPn.rotate(curAngle, vecCP);

        //add picture shift to offset
        offset += rotP - c - vecCPn;
    }

    return img;
}

bool MovableSpirit::isInScreen(const QRect &rect)
{
    return rect.intersects(bb);
}

void MovableSpirit::setPos(const QPoint &pos)
{
    bb.translate(pos - this->pos);
    this->pos = pos;
}

QList<Triangle> MovableSpirit::colModel(QRect &)
{
    QList<Triangle> colModel = spirit->getColModel();

    //rotate if necessary (todo: evaluate if faster to do this only when angle is set)
    if (fabs(curAngle) > 0.1) {
        for (Triangle &t: colModel)
            t.rotate(curAngle);
    }

    return colModel;
}

