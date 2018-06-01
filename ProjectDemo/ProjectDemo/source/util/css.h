#ifndef CSS_H
#define CSS_H

#include <QObject>
#include <QtCore>
#include <QColor>
#include <QtGui>

class CSS : public QObject
{
    Q_OBJECT
public:
    explicit CSS(QObject *parent = nullptr);

    static void initialize();

    //微软雅黑 14px
    static QFont font();
    static QSize menuFontSize();
    static QColor white();
    static QString fontStyleSheet(QString p_color, int size = 14);

private:

    QFont m_font;
    QSize m_menuFontSize;
    QColor m_white;
    QString m_MSBlackfont;

signals:

public slots:
};

#endif // CSS_H
