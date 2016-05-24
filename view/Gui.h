#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QWidget>
#include "view/widgets/LayeredWidget.h"
#include "control/util/Log.h"

//tests

#include <QLabel>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QPixmap>
#include "model/Spirit.h"
#include "control/res/SpiritManager.h"
#include <QTimer>
#include "model/GameMap.h"
#include "control/res/GameMapManager.h"
#include "control/render/Camera.h"
#include "control/render/DrawableStack.h"
#include "model/MovableSpirit.h"
#include "model/primitives/TriangleFactory.h"
#include "model/primitives/Triangle.h"
#include <QPainter>
#include <QTransform>

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

protected:
    Ui::Gui *ui;
    LayeredWidget *layers;

    //test
    QLabel *lbl;
    Camera *cam;
    bool mouseDown;
    QPoint lastMP;

    void test();
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
protected slots:
    void tick();
};

#endif // GUI_H
