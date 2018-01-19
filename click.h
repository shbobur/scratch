#ifndef CLICK_H
#define CLICK_H

#include <QWidget>
#include "dragable.h"

namespace Ui {
class Click;
}

class Click : public Dragable
{
    Q_OBJECT

public:
    explicit Click(QWidget *parent = 0);
    ~Click();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Click *ui;
};

#endif // CLICK_H
