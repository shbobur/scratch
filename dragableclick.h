#ifndef DRAGABLECLICK_H
#define DRAGABLECLICK_H

#include <QWidget>
#include "dragable.h"

namespace Ui {
class DragableClick;
}

class DragableClick : public Dragable
{
    Q_OBJECT

public:
    explicit DragableClick(QWidget *parent = 0);
    ~DragableClick();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DragableClick *ui;
};

#endif // DRAGABLECLICK_H
