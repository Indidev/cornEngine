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

void Gui::test() {

    DrawableStack *stack = new DrawableStack;

    MovableSpirit *ms = new MovableSpirit("man");
    ms->setPos(Point(400, 300));

    stack->addDrawable(ms, 10);

    ms = new MovableSpirit("knot");
    ms->setPos(Point(200, 200));

    stack->addDrawable(ms, 10);

    robotArm = new MovableSpirit("arm");
    robotArm->translate((Point(200, 200)));
    stack->addDrawable(robotArm, 10);

    stack->addDrawable(GameMapManager::getMap("testmap"), 0);

    cam = new Camera(stack, QSize(1600, 1200), QSize(800, 600));


    QWidget *pic = layers->addWidget(10);
    lbl = new QLabel;

    lbl->setPixmap(QPixmap::fromImage(*(cam->render(0))));

    QHBoxLayout *layout = new QHBoxLayout;
    pic->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addStretch();

    layout->addWidget(lbl);

    layout->addStretch();

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(1000 / 30);

}

void Gui::tick() {
    static long time = 0;
    time += 1000 / 30;


    robotArm->rotate(45 * sin((float) time / 500.f), CE::DEG, true);

    //cam->setPosition(Point(time / 10, 0));
    lbl->setPixmap(QPixmap::fromImage(*(cam->render(time))));
}

