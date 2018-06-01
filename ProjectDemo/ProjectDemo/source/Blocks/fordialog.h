#ifndef FORDIALOG_H
#define FORDIALOG_H

#include <QDialog>
#include "basedialog.h"
class ForDialog : public BaseDialog
{
    Q_OBJECT
public:
    explicit ForDialog(const QString& title, const QPoint& point, QWidget* parent = 0);
    ~ForDialog();

protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // FORDIALOG_H
