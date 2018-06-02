#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <functional>

#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QMap>
#include <QFile>
#include <QSysInfo>
#include <QMainWindow>

#define SAFE_DELETE(object)\
    if(object)\
    {\
        delete object;\
        object = NULL;\
    }\

#define SCREEN_WIDTH QApplication::primaryScreen()->availableSize().width()
#define SCREEN_HEIGHT QApplication::primaryScreen()->availableSize().height()

class CommonHelper : public QObject
{
    Q_OBJECT
public:
    explicit CommonHelper(QObject *parent = 0);
    ~CommonHelper();

    typedef std::function<void(void)> WaitHandler_t;
    void wait(int p_msec, WaitHandler_t p_handle);

    void setFilePermissions(QString p_FileName);
    void setFilePermissions(QFile& p_File);

    static CommonHelper& getInstance();

    QColor colorWithBrightness(QColor p_baseColor, int p_brightness);

private:
    QMap<QTimer*, WaitHandler_t> m_waitQueue;

public slots:

private slots:

    void onTimeout();
};

#endif // COMMONHELPER_H
