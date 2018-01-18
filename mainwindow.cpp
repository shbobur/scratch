#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include "dragable.h"
#include "dragableclick.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    view.setFilePath(QUrl::fromLocalFile("D:/dev/QtProjects/ScratchProgramming/scene.qml").toLocalFile());
//    connect(ui->pushButton, SIGNAL(clicked(bool)), &view, SLOT(show()));

    setAcceptDrops(true);
    ui->pushButton->setVisible(false);

    Dragable *dc = new DragableClick(this);
    dc->move(10, 200);
    dc->show();
    dc->setAttribute(Qt::WA_DeleteOnClose);

    dc = new DragableClick(this);
    dc->move(30, 100);
    dc->show();
    dc->setAttribute(Qt::WA_DeleteOnClose);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
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

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
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

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void MainWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/script-component")) {
        QByteArray itemData = event->mimeData()->data("application/script-component");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        //QPixmap pixmap;
        QPoint offset;
        dataStream >> offset;

        Dragable *newIcon = new DragableClick(this);

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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *childWid = childAt(event->pos());
    if (!childWid)
        return;

    QString cName = QString(childWid->metaObject()->className());
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

