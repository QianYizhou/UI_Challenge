#ifndef BLOCK_FOR_H
#define BLOCK_FOR_H

#include <QDebug>

#include "../define.h"
#include <QObject>
#include "baseblock.h"
#include "fordialog.h"
#include "blockproperty.h"
#include "../uiwidgets/projectview.h"
class Block_For : public BaseBlock
{

    Q_OBJECT

public:
    bool showconnect;
    QString GetCode();
    virtual QString GetCCode();

    void RefreshValue();
    Block_For(QPixmap p,int a);
    Block_For(QString path, int type);
    Block_For(Block_For& pB);
    ~Block_For();
    BaseBlock* clone();
    QRectF GetAllRect();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void save_node(QDomElement &self, QDomDocument &doc);

    void read_node(QDomElement &self, QDomDocument &doc);

    virtual void drawLine() override;

    virtual bool alwaysUpdateCubLine() override{return true;}

    void get_last(BaseBlock *node,int &disy,int &disx);

    virtual void SetInit(QString iconpath, QString tip, QGraphicsView* p_pProjectView, int x, int y, qreal real) override;

    virtual void updateChildPos() override;
    virtual QSize getWidgetSize() override;

    static int forNum;

public slots:
    void onParamChanged(bool bloop, int loopTimes);

private:
    /* 永远循环 */
    bool m_bForeverLoop;
    /* 循环次数 */
    int m_nLoopTimes;

    QGraphicsTextItem* m_Ytext;
    QGraphicsTextItem* m_Ntext;
    BlockProperty* m_count;
    ForDialog* m_Dialog;

    int var_a;

};

#endif // BLOCK_FOR_H
