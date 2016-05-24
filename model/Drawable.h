#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QImage>
#include <QRect>
#include <QPoint>

class Drawable
{
public:
    virtual ~Drawable() {}

    /**
     * @brief getCrop return the picture inside rect at a specific time
     * @param rect rectangle the picture should be croped from
     * @param time current game/animation time
     * @param offset offset return value
     * @return image in rect
     */
    virtual QImage *getCrop(const QRect &rect, long time, QPoint &offset) = 0;

    /**
     * @brief test if this Drawable is in screen
     * @param rect screen rectangle
     * @return wheter or not it is in
     */
    virtual bool isInScreen(const QRect &rect) = 0;
};

#endif // DRAWABLE_H
