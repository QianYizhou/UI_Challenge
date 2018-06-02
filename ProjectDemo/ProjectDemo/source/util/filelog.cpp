#include "filelog.h"
extern QString SandBoxPath;
void _WRITE_LOG_FILE_(int type , QString file, QString line , QString msg)
{
    QString err;
    switch(type){
        case QtDebugMsg:{err = "Debug：";}break;
        case QtWarningMsg:{err = "Warning：";}break;
        case QtCriticalMsg:{err = "Critical：";}break;
        case QtFatalMsg:{err = "Fatal：";}break;
        default:{err = "Info：";}break;
    }
    QString text = QString("%1 File: %2  line: %3  time: %4  \r\n message: %5 \r\n")
            .arg(err)
            .arg (file)
            .arg (line)
            .arg(QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss"))
            .arg (msg);

    qDebug() << text;
    QDir dir;
    QString path = SandBoxPath + "/log/";
    QDateTime dt = QDateTime::currentDateTime ();
    QTime t = dt.time ();
    QDate d = dt.date ();
    QString name = QString("%1%2%3%4").arg (QString::number (d.year ())).arg (QString::number (d.month ())).arg (QString::number (d.day ())).arg (QString::number (t.hour ())) + QString(".txt");
    QString filePath = path + name;
    if(!dir.exists(path))
    {
        dir.mkpath(path);
    }
    QFile files(filePath);
    if(!files.exists ())
    {
        files.open (QIODevice::WriteOnly);
        files.close ();
    }
    if(files.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&files);
        stream << text << "\r\n";
        files.flush();files.close();
    }
}
