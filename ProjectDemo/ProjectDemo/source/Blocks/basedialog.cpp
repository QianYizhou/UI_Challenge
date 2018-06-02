#include "basedialog.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QScreen>

BaseDialog::BaseDialog(const QString &title, const QPoint &point, QWidget *parent) :
    QDialog(parent)
  , m_widget(NULL)
  , m_Title(title)
  , m_TitleLabel(NULL)
  , m_pTitleLine(NULL)
  , m_bgLabel(NULL)
  , m_pClose(NULL)
{

    this->setWindowFlags(Qt::X11BypassWindowManagerHint
                         | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    resize(QSize(QApplication::primaryScreen()->availableSize().width(),
                 QApplication::primaryScreen()->availableSize().height()));


}

BaseDialog::~BaseDialog()
{

}

void BaseDialog::setTitle(const QString &title)
{
    m_Title = title;
    m_TitleLabel->setText(m_Title);
}

QString BaseDialog::getTitle()
{
    return m_Title;
}

void BaseDialog::setWidgetPoint(const QPoint &point)
{
    m_Point = point;
}

QPoint BaseDialog::getWidgetPoint()
{
    return m_Point;
}

void BaseDialog::ShowAtPosition(const QPoint &point)
{
    m_widget->move(point);
    if(point.y()<0)
    {
        QPoint p = point;
        p.setY(0);p.setX(point.x());
        m_widget->move(p);
    }
    setWidgetPoint(point);
    m_bgLabel->update();
    m_widget->update();

    show();
}

int BaseDialog::getTitleTailPosition()
{
    return m_TitleLabel->x()+m_TitleLabel->width();
}
