#include "commonhelper.h"

#include <QtCore>
#include <QWidget>
QString SandBoxPath;

CommonHelper::CommonHelper(QObject *parent) : QObject(parent)
{
}

CommonHelper::~CommonHelper()
{

}

CommonHelper& CommonHelper::getInstance()
{
    static CommonHelper thisInstance;

    return thisInstance;
}


void CommonHelper::setFilePermissions(QFile& p_File)
{
    qDebug() << p_File.fileName() <<" = chmod"<<p_File.permissions();
    if(p_File.setPermissions(QFileDevice::ReadOwner|QFileDevice::WriteOwner|QFileDevice::ExeOwner|
                              QFileDevice::ReadUser|QFileDevice::WriteUser|QFileDevice::ExeUser|
                              QFileDevice::ReadGroup|QFileDevice::WriteGroup|QFileDevice::ExeGroup|
                              QFileDevice::ReadOther|QFileDevice::WriteOther|QFileDevice::ExeOther))
    {
        qDebug() << p_File.fileName() <<" = chmod"<<p_File.permissions();
    }
}

void CommonHelper::setFilePermissions(QString p_FileName)
{
    QFile l_file(p_FileName);
    l_file.open(QFile::ReadOnly);
    setFilePermissions(l_file);
    l_file.close();
}

void CommonHelper::wait(int p_msec, WaitHandler_t p_handle)
{
    QTimer* l_pTimer = new QTimer(this);
    connect(l_pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    l_pTimer->setSingleShot(true);
    m_waitQueue[l_pTimer] = p_handle;
    l_pTimer->start(p_msec);
}

void CommonHelper::onTimeout()
{
    QTimer* l_pTimer = dynamic_cast<QTimer*>(sender());
    WaitHandler_t& l_handle = m_waitQueue[l_pTimer];
    l_handle();
    m_waitQueue.remove(l_pTimer);
    delete l_pTimer;
}

QColor CommonHelper::colorWithBrightness(QColor p_baseColor, int p_brightness)
{
    int h = 0;
    int s = 0;
    int v = 0;
    p_baseColor.getHsv(&h, &s, &v);

    return QColor::fromHsv(h, s, p_brightness);
}
