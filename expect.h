#ifndef EXPECT_H
#define EXPECT_H

#include <QWidget>

#include "dragable.h"

namespace Ui {
class Expect;
}

class Expect : public Dragable
{
    Q_OBJECT

public:
    explicit Expect(QWidget *parent = 0);
    ~Expect();

    void addWidget(QWidget *widget);

private:
    Ui::Expect *ui;
};

#endif // EXPECT_H
