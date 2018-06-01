#ifndef BLOCKPALETTE_H
#define BLOCKPALETTE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QFont>
#include <QPen>
#include <QtWidgets>
#include "../Blocks/baseblock.h"
#include "../mainwidget.h"
#include "../Blocks/blockicon.h"
class BlockCatalog : public QGraphicsObject
{
    Q_OBJECT
public:
    BlockCatalog(int p_catalogId, QString p_catalogName);

    virtual ~BlockCatalog() {}

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
    QString m_catalogName;
    int m_catalogId;
    QFont m_font;
    QPen m_pen;
};
class BlockPalette : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BlockPalette(QWidget *parent = nullptr);
    ~BlockPalette();

    struct ItemProperty_t
    {
        ItemProperty_t(int p_Id, QString p_Name, QString p_Icon, QString p_Key = "")
            :m_Id(p_Id)
            ,m_Name(p_Name)
            ,m_Icon(p_Icon)
            ,m_Key(p_Key)
        {

        }

        int m_Id;
        QString m_Name;
        QString m_Icon;
        QString m_Key;
    };

    typedef QList<ItemProperty_t> ItemPropertyList_t;

    struct catInfo{
        catInfo()
            :m_Id(0)
            ,m_startPointY(0)
        {}
        int m_Id;
        int m_startPointY;
    };

    typedef QList<catInfo> catInfoList_t;

    catInfoList_t m_catInfoList;
    int m_LastCatHeight;

    void addBlocksForCategory(int category, int catColor);

    void addBlock(BaseBlock *b);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    void loadBlocks();
    void loadControlItem();
    void loadSensorItem();
    void loadCommandItem();
protected:
    virtual void resizeEvent(QResizeEvent *event);


private:

    void emitCurrentCatChanged(int p_scrollValue);


private:

    int nextY;
    QPoint m_offset;
    bool isPress;
//    MainWidget* m_pMainWidget;

    QString scrollBarStyleSheet();

    void sceneResize();

    BaseBlock* findBlock(QGraphicsItem* target);

    void setLeftViewIconText(BlockIcon *block, QGraphicsScene *scene);
    void LoadItems(int libType, ItemPropertyList_t &p_Items);
    int calculationOffset(int libType);

signals:

    void currentCatChanged(int p_Index);
public slots:

    void onSelectedCatChanged(int p_Index);
    void onVerticalScrollBarValueChanged(int value);

};

#endif // BLOCKPALETTE_H
