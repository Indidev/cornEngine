#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMutex>

/**
 * @brief widget to display an image
 */
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief constructs a new image widget
     */
    ImageWidget(QWidget *parent = 0);

    /**
     * @brief setImage
     * @param img image to display
     */
    void setImage(QImage &img);

    /**
     * @brief setImage
     * @param img image to display
     */
    void setImage(QImage *img);

    QSize sizeHint() const Q_DECL_OVERRIDE {return size();}

protected:
    QImage img;
    QMutex mutex;

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

signals:
    void redraw();

};

#endif // IMAGEWIDGET_H
