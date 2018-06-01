#ifndef QSIZEPOLICYWIDGET_H
#define QSIZEPOLICYWIDGET_H

#include <QWidget>

enum SizePolicyType{
    SizePolicy_Equal = 1,
    SizePolicy_HFW = 2,
    SizePolicy_WFH = 3
};

class QSizePolicyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSizePolicyWidget(QWidget *parent = nullptr, SizePolicyType p_type = SizePolicy_Equal, double p_factor = 1.0);


    inline void setChildWidget(QWidget* p_child)
    {
        p_child->setParent(this);
        m_pChild = p_child;
    }

protected:

    virtual void resizeEvent(QResizeEvent* event);

private:

    QWidget* m_pChild;
    SizePolicyType m_type;
    double m_factor;

signals:

public slots:
};

#endif // QSIZEPOLICYWIDGET_H
