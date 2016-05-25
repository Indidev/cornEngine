#ifndef CAMERA_H
#define CAMERA_H

#include <QImage>
#include <QSize>
#include <QRect>

#include "control/render/DrawableStack.h"
#include "model/primitives/Point.h"

class Camera
{
public:
    /**
     * @brief constructs a new Camera
     * @param stack drawable stack
     * @param boundary broundaries the camera should keep in
     * @param viewPort viewPort of the camera
     */
    Camera(DrawableStack *stack, QSize boundary, QSize viewPort);

    /**
     * @brief setPosition
     * @param pos
     */
    void setPosition(Point pos);

    /**
     * @brief get the camera's postion
     * @return camera position
     */
    const Point &getPosition();

    /**
     * @brief change the renderSize of the camera
     * @param size new viewport size
     */
    void setViewPort(QSize size);

    /**
     * @brief renders an image
     * @param time current game/animation time
     * @return
     */
    QImage *render(long time);

protected:
    DrawableStack *stack;
    QSize boundary;
    QSize viewPort;
    Point position;
};

#endif // CAMERA_H
