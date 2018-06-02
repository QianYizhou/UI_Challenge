#ifndef MYFONT_H
#define MYFONT_H

#include "../define.h"
#include <QFontMetrics>
#include <QFont>
#include <QFontDatabase>
extern float DOTSPERINCH;
extern bool g_bIpad;    //是否是pad
extern QString strFont;

class MyFont
{
public:
    MyFont();

#if defined Q_OS_LINUX_MY

    static QFont getfont(int fontsize)
    {
        return QFont(getYaheiFont(),fontsize,QFont::Bold,false);
    }
    static QFont getfont_iphone(int fontsize)
    {
        return QFont(getYaheiFont(),fontsize,QFont::Bold,false);
    }
    static QFont getfont_normal(int fontsize)
    {
        return QFont(getYaheiFont(),fontsize,0,false);
    }
    static QFont getfont_normal_Iphone(int fontsize)
    {
        return QFont(getYaheiFont(),fontsize,0,false);
    }
    static QString getYaheiFont()
    {
        QFontDatabase fontdb;
        QStringList l_fonts = fontdb.families();
        QString fontFamily = QObject::tr("微软雅黑");
        if(l_fonts.contains(fontFamily)){}
        else{fontFamily = QObject::tr("Microsoft YaHei");}
        return fontFamily;
    }

#endif

};



#endif // MYFONT_H
