#include "fordialog.h"

ForDialog::ForDialog(const QString &title, const QPoint &point, QWidget *parent) :
    BaseDialog(title, point, parent)
{

}

ForDialog::~ForDialog()
{
}


void ForDialog::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
}
