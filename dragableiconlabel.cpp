#include "dragableiconlabel.h"

#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>

DragableIconLabel::DragableIconLabel(QWidget *parent) :
    QLabel(parent)
{

}

void DragableIconLabel::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    for (auto str : mimeData->formats()) {
        qDebug() << str << ": " << mimeData->data(str);
    }
    QPixmap pixmap;
    QString url = QUrl(mimeData->data("text/uri-list")).toLocalFile();
    qDebug() << url;
    pixmap.load(url);
    setPixmap(pixmap);
    if (mimeData->hasImage())
        setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
}
