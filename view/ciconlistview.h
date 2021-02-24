#ifndef CICONLISTVIEW_H
#define CICONLISTVIEW_H

#include <QListView>
#include <QWheelEvent>


class CIconListView: public QListView{
    Q_OBJECT
public:
    explicit CIconListView(QWidget *parent = nullptr):QListView (parent)
    {

    }
signals:
    void wheel_move(int value);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event){
        QPoint numDegrees = event->angleDelta() / 8;
        emit wheel_move(numDegrees.y());
    }
};

#endif // CICONLISTVIEW_H
