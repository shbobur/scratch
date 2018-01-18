#ifndef DRAGABLE_H
#define DRAGABLE_H

#include <QWidget>

class Dragable : public QWidget
{
    Q_OBJECT
public:
    Dragable(QWidget *parent = 0);

    QPixmap pixmap();
};

#endif // DRAGABLE_H
