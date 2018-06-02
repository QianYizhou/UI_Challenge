#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTextStream>

void _WRITE_LOG_FILE_(int type, QString file, QString line , QString msg);

#define WRITE_LOG_FILE(type, file, line, msg)\
{\
 QString fileStr = QString("%1").arg(file);\
 QString lineStr =  QString("%1").arg(line);\
 _WRITE_LOG_FILE_(type, fileStr, lineStr, msg);\
}

#ifdef QT_DEBUG

#define DEBUG_LOG(msg)(WRITE_LOG_FILE(QtDebugMsg, __FILE__, __LINE__,msg))
#define WARNING_LOG(msg)(WRITE_LOG_FILE(QtWarningMsg, __FILE__, __LINE__,msg))
#define CRITICAL_LOG(msg)(WRITE_LOG_FILE(QtCriticalMsg, __FILE__, __LINE__,msg))
#define FATAL_LOG(msg)(WRITE_LOG_FILE(QtFatalMsg, __FILE__, __LINE__,msg))
#define LOG(msg)(WRITE_LOG_FILE(-1, __FILE__, __LINE__,msg))

#else

#define DEBUG_LOG(msg)(WRITE_LOG_FILE(QtDebugMsg, "__FILE__", "__LINE__",msg))
#define WARNING_LOG(msg)(WRITE_LOG_FILE(QtWarningMsg, "__FILE__", "__LINE__",msg))
#define CRITICAL_LOG(msg)(WRITE_LOG_FILE(QtCriticalMsg, "__FILE__", "__LINE__",msg))
#define FATAL_LOG(msg)(WRITE_LOG_FILE(QtFatalMsg, "__FILE__", "__LINE__",msg))
#define LOG(msg)(WRITE_LOG_FILE(-1, "__FILE__", "__LINE__",msg))

#endif





#endif // LOG_H
