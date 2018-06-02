#include "qsizepolicywidget.h"

QSizePolicyWidget::QSizePolicyWidget(QWidget *parent, SizePolicyType p_type , double p_factor )
    : QWidget(parent)
    , m_pChild(NULL)
    , m_type(p_type)
    , m_factor(p_factor)
{

}

void QSizePolicyWidget::resizeEvent(QResizeEvent* event)
{
    if(m_pChild)
    {
        int l_width = qMin(width(), height());
        int l_height = l_width;

        switch (m_type) {
        case SizePolicy_HFW:
        {
            l_width = width();
            l_height = l_width * m_factor;
        }
            break;
        case SizePolicy_WFH:
        {
            l_height = height();
            l_width = l_height * m_factor;
        }

            break;
        default:
            break;
        }

        QRect rect((width() - l_width) / 2.0 , (height() - l_height) / 2.0, l_width, l_height);
        m_pChild->setGeometry(rect);
    }
}
