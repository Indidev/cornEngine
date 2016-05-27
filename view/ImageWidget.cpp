#include "ImageWidget.h"


ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
    connect(this, SIGNAL(redraw()), this, SLOT(update()));
}

void ImageWidget::setImage(QImage &img)
{
    //lock mutex, that way there is no redrawing while the image is set
    mutex.lock();
    this->img = img;
    //resize the widget to the images size
    resize(img.size());

    //schedule a redraw
    emit redraw();
    //unlock mutex
    mutex.unlock();
}

void ImageWidget::setImage(QImage *img)
{
    setImage(*img);
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    mutex.lock();
    QPainter p(this);
    p.drawImage(0, 0, img);
    mutex.unlock();
}
