#ifndef SPIRIT_H
#define SPIRIT_H

#include <QString>
#include <QStringList>
#include <QImage>
#include <QList>
#include <QSize>
#include <QHash>

#include "control/io/Input.h"
#include "control/util/Log.h"
#include "model/primitives/Triangle.h"
#include "model/primitives/TriangleFactory.h"
#include "model/primitives/Point.h"

/**
 * @brief Representation of a Spirit
 */
class Spirit
{
public:

    static const QString TAG;
    static const QString FRMS;
    static const QString FSZE;
    static const QString IMG;
    static const QString NUMF;
    static const QString FPOS;
    static const QString COL;
    static const QString FPS;
    static const QString FTME;
    static const QString DIR;
    static const QString PIV;
    static const QString ROOT;

    /**
     * @brief creates a new spirit out of a configuration
     * @param config configuration
     */
    Spirit(QHash<QString, QString> &config);

    /**
     * @brief get a frame of this spirit, according to the current animation time
     * @param ms animation time in milli seconds
     * @return frame for time ms
     */
    const QImage &getFrame(long ms);

    /**
     * @brief get the size of this spirit
     * @return size of spirit
     */
    const QSize &getSize();

    /**
     * @brief getColModel
     * @return collision model of this spirit, empty list if non exists
     */
    const QList<Triangle> getColModel();

    /**
     * @brief hasColModel
     * @return true if spirit has collision model
     */
    bool hasColModel();

    /**
     * @brief getPivot
     * @return get the point to rotate the spirit around
     */
    Point getPivot();

    /**
     * @brief getroot
     * @return get the point the spirit should be placed with
     */
    Point getroot();

protected:

    static const QString LOG_TAG;

    QString tag;
    QList<QImage> frames;
    QList<Triangle> colModel;
    QSize frameSize;
    Point rootP;
    Point pivotP;

    int frameTime;
    bool hasCol;

    Point splitNum(QString input);
};

#endif // SPIRIT_H
