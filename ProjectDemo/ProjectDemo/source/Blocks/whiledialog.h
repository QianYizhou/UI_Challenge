#ifndef WHILEDIALOG_H
#define WHILEDIALOG_H

#include <QDialog>
#include "basedialog.h"

class WhileDialog : public BaseDialog
{
    Q_OBJECT
public:
    explicit WhileDialog(const QString& title, const QPoint& point, QWidget* parent = 0);
    ~WhileDialog();

protected:
    void mousePressEvent(QMouseEvent *event);


};

#endif // WHILEDIALOG_H
