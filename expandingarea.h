#ifndef EXPANDINGAREA_H
#define EXPANDINGAREA_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class ExpandingArea;
}

class ExpandingArea : public QWidget
{
    Q_OBJECT

public:
    explicit ExpandingArea(QWidget *parent = 0);
    ~ExpandingArea();

    void addWidget(QWidget *w);

protected:
    void paintEvent(QPaintEvent *event);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::ExpandingArea *ui;
    QList<QWidget*> childList;

    QVBoxLayout *mainLayout;
    int contentHeight;
};

#endif // EXPANDINGAREA_H
