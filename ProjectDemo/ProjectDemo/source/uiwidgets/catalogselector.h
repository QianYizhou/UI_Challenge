#ifndef CATALOGSELECTOR_H
#define CATALOGSELECTOR_H

#include <QWidget>
#include <QPixmap>

#include <QtCore>
#include <QtWidgets>

class CatalogItem : public QPushButton
{
    Q_OBJECT
public:
    CatalogItem(int p_catId, QString pIcon, QString p_BgImage, QWidget *parent = nullptr);
    virtual ~CatalogItem();

    void setChecked(bool, bool emitevent = true);

    inline void setName(const QString& text)
    {
        m_pNameLabel->setText(text);
    }

    inline QString name()
    {
       return  m_pNameLabel->text();
    }

    inline int catId()
    {
        return m_catId;
    }

    void updateFontSize(QFont& p_Font);

    static QFont s_defaultFont;

private:
    int m_catId;
    QString m_Icon;
    QString m_BgImage;

    QLabel* m_pNameLabel;

signals:
    void buttonClicked(bool checked = false);

public slots:
    void onButtonClicked(bool checked = false);
    QString getModuleNameByID();
};

class CatalogSelector : public QWidget
{
    Q_OBJECT
public:
    explicit CatalogSelector(QWidget *parent = nullptr);

    void Initialize();

protected:

    virtual void resizeEvent(QResizeEvent* event);
    virtual void wheelEvent(QWheelEvent *event);

private:

    QWidget* m_pBackground;
    QWidgetList m_catalogs;
    CatalogItem* m_currentSelected;

    void setSelected(CatalogItem* p_pCurrentSelected , bool emitevent = true);

    void updateFontSize();

    void getCatalogNames(QStringList& p_textList);

    int getTextMaxWidth(QFont& p_font, QStringList& textList);

signals:
    void selectedItemChanged(int p_Index);
public slots:
    void onButtonClicked(bool checked = false);

    void onCurrentCatChanged(int p_Index);
};

#endif // CATALOGSELECTOR_H
