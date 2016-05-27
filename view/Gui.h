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
#include "model/Types.h"
#include "math.h"
#include "model/interface/TimeListener.h"
#include "control/Timer.h"
#include <QMutex>
#include "view/ImageWidget.h"

using std::sin;

namespace Ui {
class Gui;
}

class Gui : public QMainWindow, TimeListener
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    void onTime(long time, int delta);

protected:
    Ui::Gui *ui;
    LayeredWidget *layers;

    //test
    ImageWidget *camWidget;
    Camera *cam;
    bool mouseDown;
    Point lastMP;
    MovableSpirit *robotArm;
    QLabel *imgLbl;
    Timer timer;
    QMutex lock;

    void test();
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *);

    void resizeEvent(QResizeEvent *ev);
protected slots:
};

#endif // GUI_H
