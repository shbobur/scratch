#include "click.h"
#include "ui_click.h"

#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QColor>
#include <QTime>
#include <QPoint>
#include <QPainterPath>

Click::Click(QWidget *parent) :
    Dragable(parent),
    ui(new Ui::Click)
{
    ui->setupUi(this);

//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_PaintOnScreen);
}

Click::~Click()
{
    delete ui;
}

void Click::paintEvent(QPaintEvent *event)
{
//    QStyleOption o;
//    o.initFrom(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);

    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(10, 0);
    path.lineTo(13, 3);
    path.lineTo(25, 3);
    path.lineTo(28, 0);
    path.lineTo(width()-1, 0);
    path.lineTo(width()-1, height()-4);
    path.lineTo(28, height()-4);
    path.lineTo(25, height()-1);
    path.lineTo(13, height()-1);
    path.lineTo(10, height()-4);
    path.lineTo(0,  height()-4);
    path.lineTo(0, 0);
//! [8]

//! [9]
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setColor(QColor(2, 5, 138));
    QBrush brush(QColor(3, 10, 250, 128));
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.save();
    painter.drawPath(path);
    painter.restore();

}

