#include "dragable.h"

#include <QPixmap>
#include <QRect>
#include <QPoint>
#include <QRegion>

Dragable::Dragable(QWidget *parent):
    QWidget(parent)
{
}

QPixmap Dragable::pixmap()
{
    QRect rectangle = this->rect();
    QPixmap screenshot(rectangle.size());
    this->render(&screenshot, QPoint(), QRegion(rectangle));
    return screenshot;
}
