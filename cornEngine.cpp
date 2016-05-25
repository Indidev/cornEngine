#include "view/Gui.h"
#include <QApplication>

//test includes
#include <QHash>
#include <QString>
#include "control/io/Input.h"
#include "control/util/Log.h"
#include "model/Spirit.h"
#include "model/GameMap.h"
#include "control/res/GameMapManager.h"
#include <QRect>
#include "model/primitives/Triangle.h"
#include <QList>
#include <math.h>
#include "model/primitives/Point.h"

void test();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();

    test();

    return a.exec();
}

void test() {
}
