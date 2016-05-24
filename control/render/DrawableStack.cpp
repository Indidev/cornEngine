#include "DrawableStack.h"

const QString DrawableStack::TAG = "control/util/Log";

DrawableStack::DrawableStack()
{
    renderImg = NULL;
}

QImage *DrawableStack::render(QRect rect, long time)
{
    //delete image if allready present
    if (renderImg)
        delete renderImg;

    //prepare Image
    renderImg = new QImage(rect.size(), QImage::Format_ARGB32);
    renderImg->fill(Qt::transparent);
    QPainter p(renderImg);

    //itterate through all indexes
    for (int index : keys) {
        //itterate through all items at $index
        for (Drawable *d : zIndexed[index]) {
            if (d->isInScreen(rect)) {
                Point offset(0, 0);
                QImage *img = d->getCrop(rect, time, offset);
                p.drawImage(offset, *img);
            }
        }
    }

    return renderImg;
}

void DrawableStack::addDrawable(Drawable *item, int zIndex)
{
    if (item == NULL) {
        Log::e(TAG, "item is null", "addDrawable(Drawable*, int)");
        return;
    }
    if (stack.contains(item))
        removeDrawable(item);

    stack[item] = zIndex;
    zIndexed[zIndex].append(item);

    //add key if not present
    if (!keys.contains(zIndex)) {
        int i;
        for (i = 0; i < keys.length() && keys[i] < zIndex; i++);
        keys.insert(i, zIndex);
    }
}

void DrawableStack::removeDrawable(Drawable *item)
{
    if (stack.contains(item)) {
        int index = stack[item];
        stack.remove(item);
        zIndexed[index].removeOne(item);
    }
}

void DrawableStack::clear()
{
    stack.clear();
    zIndexed.clear();
}
