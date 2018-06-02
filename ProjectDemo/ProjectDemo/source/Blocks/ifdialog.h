#ifndef IFDIALOG_H
#define IFDIALOG_H

#include <QDialog>
#include "basedialog.h"

class IfDialog : public BaseDialog
{
    Q_OBJECT
public:
    explicit IfDialog(const QString& title, const QPoint& point, QWidget* parent = 0);
    ~IfDialog();

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // IFDIALOG_H
