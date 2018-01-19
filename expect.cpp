#include "expect.h"
#include "ui_expect.h"

#include "expandingarea.h"

Expect::Expect(QWidget *parent) :
    Dragable(parent),
    ui(new Ui::Expect)
{
    ui->setupUi(this);

    resize(minimumSizeHint());
    update();
}

Expect::~Expect()
{
    delete ui;
}

void Expect::addWidget(QWidget *widget)
{
    ui->foundAreaWidget->addWidget(widget);
    resize(minimumSizeHint() + ui->foundAreaWidget->minimumSizeHint());
    update();
}
