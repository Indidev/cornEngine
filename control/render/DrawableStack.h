#ifndef DRAWABLESTACK_H
#define DRAWABLESTACK_H

#include <QHash>
#include <QList>
#include <QImage>
#include <QPainter>
#include <QRect>

#include "model/interface/Drawable.h"
#include "control/util/Log.h"
#include "model/primitives/Point.h"

class DrawableStack
{
public:
    DrawableStack();

    /**
     * @brief render camera picture
     * @param rect view rectangle of camera
     * @param time current game-time
     * @return camera image
     */
    QImage *render(QRect rect, long time);

    /**
     * @brief add a drawable to the stack <br>
     * every drawable is only once in the stack
     * @param item item to add
     * @param zIndex z-index of item
     */
    void addDrawable(Drawable* item, int zIndex = 0);

    /**
     * @brief remove a drawable from the stack
     * @param item drawable to remove
     */
    void removeDrawable(Drawable* item);

    /**
     * @brief clear the stack
     */
    void clear();

protected:
    static const QString TAG;
    QHash<Drawable*, int> stack;
    QHash<int, QList<Drawable*> > zIndexed;
    QList<int> keys;
    QImage *renderImg;
};

#endif // DRAWABLESTACK_H
