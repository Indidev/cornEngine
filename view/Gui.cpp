#include "Gui.h"
#include "ui_Gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);

    centralWidget()->setLayout(new QGridLayout);

    QLayout *cL = centralWidget()->layout();
    cL->setSpacing(0);
    cL->setMargin(0);
    layers = new LayeredWidget;
    cL->addWidget(layers);
    test();
}

Gui::~Gui()
{
    delete ui;
}

void Gui::mouseMoveEvent(QMouseEvent *event)
{
    Point delta = event->globalPos() - lastMP;
    lastMP = event->globalPos();
    cam->setPosition(cam->getPosition() - delta);
}

void Gui::mousePressEvent(QMouseEvent *event)
{
    if (!mouseDown) {
        mouseDown = true;
        lastMP = event->globalPos();
    }
}

void Gui::mouseReleaseEvent(QMouseEvent *)
{
    mouseDown = false;
}

void Gui::resizeEvent(QResizeEvent *ev)
{
    lock.lock();
    QMainWindow::resizeEvent(ev);
    lock.unlock();
}

void Gui::test() {

    DrawableStack *stack = new DrawableStack;

    MovableSpirit *ms = new MovableSpirit("man");
    ms->setPos(Point(400, 300));

    stack->addDrawable(ms, 10);

    ms = new MovableSpirit("knot");
    ms->setPos(Point(200, 200));

    stack->addDrawable(ms, 10);

    k = new Kinematic;
    k->setPos(Point(400, 300));
    stack->addDrawable(k, 10);

    robotArm = new MovableSpirit("arm");
    robotArm->translate((Point(200, 200)));
    stack->addDrawable(robotArm, 10);

    stack->addDrawable(GameMapManager::getMap("testmap"), 0);

    cam = new Camera(stack, QSize(1600, 1200), QSize(800, 600));


    QWidget *pic = layers->addWidget(10);
    camWidget = new ImageWidget;

    camWidget->setImage(cam->render(0));
    //camWidget->setPixmap(QPixmap::fromImage(*(cam->render(0))));

    QHBoxLayout *layout = new QHBoxLayout;
    pic->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addStretch();

    layout->addWidget(camWidget);

    layout->addStretch();

    timer.subscribe(this);
    timer.start(1000 / 60);

}

void Gui::onTime(long time, int delta)
{
    Log::d("Gui", "delta: " + QString::number(delta));
    robotArm->rotate(45 * sin((float) time / 500.f), CE::DEG, true);
    //k->getRootNode()->rotate(50, CE::DEG);
    //k->getRootNode()->rotate(0.1, CE::DEG);
    k->getRootNode()->rotate(50 * sin((float) time / 500.f), CE::DEG, true);
    k->getRootNode()->getChildren()[0]->rotate(5, CE::DEG);

    //cam->setPosition(Point(time / 10, 0));

    //QImage *render = cam->render(time);
    camWidget->setImage(cam->render(time));
    //camWidget->setPixmap(QPixmap::fromImage(*render));
}

