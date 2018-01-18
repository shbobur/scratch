#ifndef DRAGABLEICONLABEL_H
#define DRAGABLEICONLABEL_H

#include <QLabel>

class DragableIconLabel : public QLabel
{
    Q_OBJECT

public:
    DragableIconLabel(QWidget *parent = 0);

protected:
    void dropEvent(QDropEvent *event);
};

#endif // DRAGABLEICONLABEL_H
