#include "css.h"

#include <QtCore>

CSS g_css;

CSS::CSS(QObject *parent) : QObject(parent)
{

}

void CSS::initialize()
{
    g_css.m_white = QColor::fromRgb(255,255,255);

    QFontDatabase fontdb;
    QStringList l_fonts = fontdb.families();


    QString fontFamily;
    if(l_fonts.contains("Microsoft YaHei"))
    {
        fontFamily = "Microsoft YaHei";
    }
    else
    {
        fontFamily = g_css.m_font.defaultFamily();
    }

    g_css.m_font = QFont(fontFamily);
    g_css.m_MSBlackfont = fontFamily;
    g_css.m_font.setPixelSize(14);

    //m_font = QFont
}

QFont CSS::font()
{
    return g_css.m_font;
}

QString CSS::fontStyleSheet(QString p_color, int size)
{
    QString stylesheet;
    stylesheet.append(QString(" color:%1; ").arg(p_color));
    stylesheet.append(QString(" font-size:%1px; ").arg(size));
    stylesheet.append(QString(" font-family:\"%1\"; ").arg(g_css.m_MSBlackfont));
    return stylesheet;
}

QSize CSS::menuFontSize()
{
    return g_css.m_menuFontSize;
}
QColor CSS::white()
{
    return g_css.m_white;
}
