#include "expandingarea.h"
#include "ui_expandingarea.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

#include "dragable.h"
#include "click.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPixmap>
#include <QDebug>
#include <QLabel>

ExpandingArea::ExpandingArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpandingArea)
{
    ui->setupUi(this);

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    contentHeight = 0;
}

ExpandingArea::~ExpandingArea()
{
    delete ui;
}

void ExpandingArea::addWidget(QWidget *widget)
{
    childList.append(widget);
    mainLayout->addWidget(widget);
    contentHeight += widget->maximumHeight() + 3;
    resize(minimumSizeHint());
    update();
}

void ExpandingArea::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(width()-1, 0);
    path.lineTo(width()-1, height()-1);
    path.lineTo(0, height()-1);
    path.lineTo(0, 0);

    QPainter painter(this);
    painter.drawPath(path);
}

void ExpandingArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/script-component")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        Dragable *child = static_cast<Dragable*>(this->childAt(event->pos()));
        event->setDropAction(Qt::MoveAction);
        //child->handleDrop(event);
        event->accept();
        //event->ignore();
    }
}

void ExpandingArea::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/script-component")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ExpandingArea::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void ExpandingArea::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/script-component")) {
        QByteArray itemData = event->mimeData()->data("application/script-component");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        //QPixmap pixmap;
        QPoint offset;
        dataStream >> offset;

        Dragable *newIcon = new Click(this);

        //newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ExpandingArea::mousePressEvent(QMouseEvent *event)
{
    QWidget *childWid = childAt(event->pos());
    if (!childWid)
        return;

    QString cName = QString(childWid->metaObject()->className());
    if (cName == QString("ExpandingArea"))
        return ;

    if (cName == QString("DescriptionLabel") || cName == "ImageStoreLabel") {
        childWid = childWid->parentWidget();
        Dragable *obj = new Dragable;
        if (!childWid->metaObject()->inherits(obj->metaObject()))
            return;
    }


    Dragable *child = static_cast<Dragable*>(childWid);
    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QPoint(event->pos() - child->pos());
//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/script-component", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
//! [3]

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
      //  child->setPixmap(pixmap);
    }
}
