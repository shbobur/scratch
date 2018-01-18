#ifndef DRAGTOUCHWIDGET_H
#define DRAGTOUCHWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "dragable.h"

namespace Ui {
class DragTouchWidget;
}

class DragTouchWidget : public Dragable
{
    Q_OBJECT

public:
    explicit DragTouchWidget(QWidget *parent = 0);
    ~DragTouchWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DragTouchWidget *ui;
    int currentTempNumber;
    QString tempNameBase;
};

#endif // DRAGTOUCHWIDGET_H
