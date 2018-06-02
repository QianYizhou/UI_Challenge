#include "whiledialog.h"

WhileDialog::WhileDialog(const QString &title, const QPoint &point, QWidget *parent) :
    BaseDialog(title, point, parent)

{

}

WhileDialog::~WhileDialog()
{
}


void WhileDialog::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
}
