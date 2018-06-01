#include "NScrollBar.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
NScrollBar::NScrollBar(QWidget *parent) :
    QScrollBar(parent)
  , _handle(NULL)
  , _valueAnimation(NULL)
  , _minimum(0)
  , _maximum(0)
  , _value(0)
  , _handle_y(0)
{
    _valueAnimation = new QPropertyAnimation(this, "value");
    _valueAnimation->setEasingCurve(QEasingCurve::OutQuad);

    initUI();
    connect(this, SIGNAL(rangeChanged(int,int)), this, SLOT(setNRange(int,int)));
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setNValue(int)));
}


QSize NScrollBar::sizeHint() const
{
    return QSize(975*g_fScaleX, 20*g_fScaleY);
}

void NScrollBar::initUI()
{
    setObjectName("NScrollBar");
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("#NScrollBar{border:0px;background-color:transparent;}");

    _handle = new NHandle(this);
    _handle->setObjectName("handle");
    _handle->setFocusPolicy(Qt::NoFocus);
    _handle->setCheckable(false);
    _handle->setStyleSheet("#handle{border:0px;border-image:url(:res/windows/skillcreator/handle.png) center no-repeat;}");
    _handle->setGeometry(0, _handle_y, 53*g_fScaleX, 37*g_fScaleY);

    setFixedHeight(_handle->height());

    connect(_handle, SIGNAL(handleMoved(int)), this, SLOT(reCalcValue(int)));
}


void NScrollBar::refreshHandlePosition()
{
    int maxWidth = frameSize().width() - _handle->width();
    if(_maximum == 0){
        _handle->setGeometry(0, _handle_y, 53*g_fScaleX, 37*g_fScaleY);
        return;
    }
    double pos = (double)_value / (double)_maximum * (double)maxWidth;
    _handle->setGeometry(qMin(maxWidth, (int)pos), _handle_y, 53*g_fScaleX, 37*g_fScaleY);//65
    _handle->update();
    update();
}


void NScrollBar::setValueWithAnimate(int newValue)
{
    if(_valueAnimation->state() == QPropertyAnimation::Running)
    {
        _valueAnimation->stop();
    }

    if(newValue <= width()){
        int stateValue = _value;
        emit scrollToMin();
        if(stateValue < _value){
            newValue = newValue + (_value - stateValue);
        }
    }

    _valueAnimation->setStartValue(value());
    _valueAnimation->setEndValue(newValue);

    double distance = qAbs(newValue - value());
    double time = (double)maximum() / (double)width() / 2.0 * 600.0 * (distance / (double)width());
    time = qMin(600.0, time);
    _valueAnimation->setDuration(time);
    _valueAnimation->start();
//    qDebug()<<"newValue = "<<newValue;
    emit scrollToZoomInOut(newValue,_maximum);
}


void NScrollBar::reCalcValue(int pos)
{
//    qDebug()<<"NScrollBar::reCalcValue() ++++++++++++++++++++ ";
    int maxWidth = frameSize().width() - _handle->width();
//    qDebug()<<"frameSize().width() ="<<frameSize().width();
//    qDebug()<<"_handle->width() ="<<_handle->width();
//    qDebug()<<"maxWidth ="<<maxWidth;
    if(_maximum == 0){
        _handle->setGeometry(0, _handle_y, 53*g_fScaleX, 37*g_fScaleY);
        return;
    }
    double value = (double)pos /(double)maxWidth * (double)_maximum;
    value = qMin((int)value, _maximum);

//    qDebug()<<"value = "<<value;
//    qDebug()<<"pos ="<<pos;
//    qDebug()<<"_maximum ="<<_maximum;
    setValueWithAnimate((int)value);
}


void NScrollBar::setNRange(int min, int max)
{
    _minimum = min;
    _maximum = max;
//    qDebug()<<"min="<<min<<"max="<<max;
    refreshHandlePosition();
}


void NScrollBar::setNValue(int value)
{
    _value = value;
    refreshHandlePosition();
}


void NScrollBar::paintEvent(QPaintEvent *event)
{
    _handle_y = (rect().height() - 37*g_fScaleY) / 2 - 3;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    painter.save();
    painter.translate(0, (rect().height() - 20*g_fScaleY)/2);
    QRect bgRect = rect();
//    qDebug()<<"bgRect = "<<bgRect;
    bgRect.setWidth(bgRect.width() - 5);
    bgRect.setHeight(20*g_fScaleY);
    painter.drawPixmap(bgRect,QPixmap(":res/windows/skillcreator/time_scroll_bg.png"));
    painter.restore();

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QWidget::paintEvent(event);
}


void NScrollBar::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    reCalcValue(event->pos().x());
}


void NScrollBar::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 120;

    int x = 0;
    if(numDegrees.isNull()){
        x = numPixels.rx();
    }else{
        x = numDegrees.ry();
    }
//    qDebug()<<"NScrollBar::wheelEvent pageStep()"<<pageStep()<<x;
    x = value() - pageStep() * 72 * x;
    if(x > 0){
        x = qMin(_maximum, x);
    }else{
        x = 0;
    }

    setValueWithAnimate(x);
}

void NScrollBar::resizeEvent(QResizeEvent *event)
{
    refreshHandlePosition();
    QScrollBar::resizeEvent(event);
}


NHandle::NHandle(QWidget *parent) :
    QPushButton(parent)
  , _isDrag(false)
{

}


void NHandle::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        _isDrag = true;
        _lastWidth = event->globalX() - frameGeometry().topLeft().x();
        event->accept();
    }
    _isDrag = true;
}


void NHandle::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        _isDrag = false;
        event->accept();
    }
}


void NHandle::mouseMoveEvent(QMouseEvent *event)
{
    if (_isDrag){
//        qDebug()<<"NScrollBar::mouseMoveEvent() ++++++++++++++++++++ ";
        int targetWidth = event->globalX() - _lastWidth;
//        qDebug()<<"event->globalX() ="<<event->globalX();
//        qDebug()<<"_lastWidth ="<<_lastWidth;
//        qDebug()<<"targetWidth ="<<targetWidth;


        int maxWidth = parentWidget()->frameSize().width() - frameGeometry().width();

//        qDebug()<<"parentWidget()->frameSize().width() ="<<parentWidget()->frameSize().width();
//        qDebug()<<"frameGeometry().width() ="<<frameGeometry().width();
//        qDebug()<<"maxWidth ="<<maxWidth;
        if(targetWidth > maxWidth){
            targetWidth = maxWidth;
        }
        if(targetWidth < 0){
            targetWidth = 0;
        }

        event->accept();

        emit handleMoved(targetWidth);
    }
}
