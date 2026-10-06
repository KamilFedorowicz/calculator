#include "aboutdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("About Calculator");
    setFixedSize(300, 200);

    QLabel *title = new QLabel("<b>Calculator</b>", this);

    QLabel *version = new QLabel("Version 1.0", this);

    QLabel *description = new QLabel("A calculator application built with C++ and Qt.", this);

    description->setWordWrap(true);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok, this);

    connect(
        buttons,
        &QDialogButtonBox::accepted,
        this,
        &QDialog::accept
            );

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(title);
    layout->addWidget(version);
    layout->addWidget(description);
    layout->addStretch();
    layout->addWidget(buttons);
}
