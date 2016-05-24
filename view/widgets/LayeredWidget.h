#ifndef LAYEREDWIDGET_H
#define LAYEREDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QPair>

/**
 * @brief The LayeredWidget class
 * widget with multiple layers, managed via z-index
 */
class LayeredWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * create new layered widget
     */
    explicit LayeredWidget();

    /**
     * get a new widget at the given position
     * @param z_index z-index of the new widget
     * @return a widget for your stuff
     */
    QWidget *addWidget(int z_index);

    /**
     * removes a layer
     * @param widget widget to remove
     */
    void removeWidget(QWidget *widget);
signals:

public slots:

protected:
    QList<QPair<QWidget*, int> > layers;
    QWidget *contentWidget;

    void resizeEvent(QResizeEvent *event);
};

#endif // LAYEREDWIDGET_H
