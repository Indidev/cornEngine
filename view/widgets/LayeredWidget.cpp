#include "LayeredWidget.h"

LayeredWidget::LayeredWidget()
{
    this->setLayout(new QGridLayout);
    contentWidget = new QWidget;
    this->layout()->setMargin(0);
    this->layout()->setSpacing(0);
    this->layout()->addWidget(contentWidget);
}

QWidget *LayeredWidget::addWidget(int z_index)
{
    QWidget *widget = new QWidget(contentWidget);
    widget->setStyleSheet("background-color:transparent");

    QPair<QWidget*, int> newElement(widget, z_index);
    int i;
    //find position
    for (i = 0; i < layers.size() && layers[i].second > z_index; i++);
    //insert element
    layers.insert(i, newElement);
    if (i > 0)
        newElement.first->stackUnder(layers[i - 1].first);

    return widget;
}

void LayeredWidget::removeWidget(QWidget *widget)
{
    for (int i = 0; i < layers.size(); i++) {
        if (layers[i].first == widget) {
            widget->deleteLater();
            layers.removeAt(i);
            break;
        }
    }
}

void LayeredWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    for (QPair<QWidget*, int> widget: layers) {
        widget.first->setGeometry(this->geometry());
    }
}
