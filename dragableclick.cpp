#include "dragableclick.h"
#include "ui_dragableclick.h"

#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>

DragableClick::DragableClick(QWidget *parent) :
    Dragable(parent),
    ui(new Ui::DragableClick)
{
    ui->setupUi(this);
}

DragableClick::~DragableClick()
{
    delete ui;
}

void DragableClick::paintEvent(QPaintEvent *event)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

