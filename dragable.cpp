#include "dragable.h"

Dragable::Dragable(QWidget *parent) :
    QWidget(parent)
{

}

QPixmap Dragable::pixmap()
{
    QRect rectangle = this->rect();
    QPixmap pixmap(rectangle.size());
    this->render(&pixmap, QPoint(), QRegion(rectangle));
    return pixmap;
}
