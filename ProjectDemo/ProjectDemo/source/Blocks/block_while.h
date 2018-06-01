#ifndef BLOCK_WHILE_H
#define BLOCK_WHILE_H

#include <QDebug>
#include "../define.h"
#include <QObject>
#include "baseblock.h"
#include "whiledialog.h"
#include "blockproperty.h"
class Block_While : public BaseBlock
{

    Q_OBJECT

public:
    bool showconnect;
    QString GetCode();
    virtual QString GetCCode();

    void RefreshValue();
    Block_While(QPixmap p,int a);
    Block_While(QString path, int type);
    Block_While(Block_While& pB);
    ~Block_While();
    BaseBlock* clone();
    QRectF GetAllRect();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void save_node(QDomElement &self, QDomDocument &doc);

    void read_node(QDomElement &self, QDomDocument &doc);

    virtual void drawLine() override;

    virtual bool alwaysUpdateCubLine() override{return true;}

    virtual void SetInit(QString iconpath, QString tip, QGraphicsView* p_pProjectView, int x, int y, qreal real) override;

    virtual void updateChildPos() override;
    virtual QSize getWidgetSize() override;

public slots:
    void onParamChanged(QString);

private:
    QString whileString;

    QGraphicsTextItem* m_Ytext;
    QGraphicsTextItem* m_condition;
    QGraphicsTextItem* m_Ntext;
};

#endif // BLOCK_WHILE_H
