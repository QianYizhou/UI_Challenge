#include "ifdialog.h"

IfDialog::IfDialog(const QString &title, const QPoint &point, QWidget *parent) :
    BaseDialog(title, point, parent)

{

}

IfDialog::~IfDialog()
{
}

void IfDialog::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
}
