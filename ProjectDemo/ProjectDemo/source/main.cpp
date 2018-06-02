#include "mainwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QDialog>

float g_fScale = 1.0;
qreal factor = 1.0;
qreal g_fScaleX = 1.0;
qreal g_fScaleY = 1.0;
int WINDOWRectWidth = 1920;
int WINDOWRectHeight = 1080;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    g_fScale = factor*1/QApplication::primaryScreen()->devicePixelRatio();
    g_fScaleX = (qreal)((qreal)factor*QApplication::primaryScreen()->availableSize().width()/(qreal)WINDOWRectWidth);
    g_fScaleY = (qreal)((qreal)factor*QApplication::primaryScreen()->availableSize().height()/(qreal)WINDOWRectHeight);
    qDebug()<<"g_fScale = "<<g_fScale<<g_fScaleX<<g_fScaleY;
    qDebug("QApplication::primaryScreen()->size()    %d      %d", QApplication::primaryScreen()->size().width(),
            QApplication::primaryScreen()->size().height());
    qDebug()<<"QApplication::primaryScreen()->logicalDotsPerInch() ="<<QApplication::primaryScreen()->logicalDotsPerInch();
    QScreen *screen = qApp->screens().at(0);
    qDebug() << screen->geometry()<< screen->physicalSize() << screen->physicalDotsPerInch()<<QApplication::primaryScreen()->devicePixelRatio();
    qDebug("QApplication::desktop()->screenGeometry()    %d      %d", QApplication::desktop()->screenGeometry().width(),
            QApplication::desktop()->screenGeometry().height());
    qDebug("QApplication::primaryScreen()->logicalDotsPerInch()  %f", QApplication::primaryScreen()->logicalDotsPerInch());

    MainWidget w;
    w.show();

    return a.exec();
}
