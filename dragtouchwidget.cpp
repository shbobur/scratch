#include "dragtouchwidget.h"
#include "ui_dragtouchwidget.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

#include "draglabel.h"

DragTouchWidget::DragTouchWidget(QWidget *parent) :
    Dragable(parent),
    ui(new Ui::DragTouchWidget)
{
    ui->setupUi(this);
   setAcceptDrops(false);
}

DragTouchWidget::~DragTouchWidget()
{
    delete ui;
}

void DragTouchWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
