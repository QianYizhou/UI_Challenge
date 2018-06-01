#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QGraphicsView>
#include <QPropertyAnimation>

#include <QDomElement>
#include <QDomDocument>

#include "percubeline.h"
#include "connectblock.h"
class BaseBlock : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    BaseBlock();
    BaseBlock(QPixmap p,int id);
    BaseBlock(QString file, int id, int type = 0);
    BaseBlock(const QString &file, const QString &text, QSize imagesize);
    virtual ~BaseBlock();

    void setBaseBlockID(int id);
    int getBaseBlockID()const;

    int circleinside;
    int leaf;
    bool isfirst;
    bool you;
    int Layerno;
    PerCubeLine *cubline;
    PerCubeLine * cubline_left;
    PerCubeLine * cubline_right;

    BaseBlock *leftnode;
    BaseBlock *rightnode;
    BaseBlock *nextnode;
    BaseBlock *prenode;
    BaseBlock* stepNode;

    ConnectBlock* nextStep;
    ConnectBlock *left;
    ConnectBlock *right;
    ConnectBlock *next;
    /* 碰撞检测模块 */
    ConnectBlock *collisionBlock;
    QGraphicsLineItem *myline;

    int cnt;
    QPropertyAnimation *anim;

    int Leftcnt;
    int Rightcnt;
    int LeftTotalcnt;
    int RightTotalcnt;

    int LineLeft;
    int LineRight;

    void ask(BaseBlock *node);
    virtual void drawLine(/*BaseBlock *node*/);
    void invaline(BaseBlock *node);

    QPoint copypresspt;
    bool isConnect;
    bool isediting;
    bool isMove;
    QPainterPath path;

    QPointF dispoint;

    QString filepath;
    QString pixmapPath;
    int ID;
    int blockactionNumber;
    QString myText;

    QPixmap iconPixmap;
    int blockType;
    //setup function
    void setBlockType(const int& type);
    int getBlockType();
    void setIconPixmap(const QPixmap &pixmap);
    void setIconPixmap(const QString &pixmapstr);
    QPixmap getIconPixmap();
    void setMyPixmap(const QString &file, QSize size);
    void setMyPixmap(const QPixmap &pixmap);
    virtual void setMyText(const QString &text);
    QString getMyText();
    //virtual function
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void SetInit(QString iconstr, QString tip, QGraphicsView *p_pProjectView, int x, int y, qreal real);

    virtual void save_node(QDomElement &self,QDomDocument &doc) = 0;
    virtual void read_node(QDomElement &self,QDomDocument &doc) = 0;
    virtual BaseBlock* clone() = 0;
    virtual QString GetCode() = 0;

    virtual QString GetCCode()
    {
        return this->GetCode();
    }

    void get_rect_head_end(BaseBlock *node_head,BaseBlock *node_end,double &lefttopx,double &lefttopy,double &rightbottomx,double &rightbottomy);

    virtual int getBlockactionNumber(){return -1;}
    virtual QString getVarName(){return "";}

    virtual void getvalue(int &type,QString &str){type = -1;str = "";}
    virtual QSize getWidgetSize(){return QSize(0, 0);}

    void SetTree(BaseBlock *node, QGraphicsSceneMouseEvent *event);
    virtual void DelList(BaseBlock *node);

    /**
     * @brief 碰撞检测
     */
    bool dealCollision();

    virtual bool alwaysUpdateCubLine();

    /**
     * @brief 更新连接线
     */
    virtual void updateConnetLine();

    virtual void updateNodePos();

    /**
     * @brief 更新连接子节点的位置
     * @param Xoffset
     * @param Yoffset
     */
    void updateConnectNode(qreal Xoffset, qreal Yoffset);

    int get_leftCount();

    /**
     * @brief 左右节点个数
     */
    int get_rightCount();

    int get_leaf(BaseBlock*);

    void updateAllConnectPos();

    virtual void updateChildPos();

    void getRectSize(BaseBlock* node, qreal &xLeft, qreal &yButton, qreal &xRight, int& lloop, int& rloop);

    int loop_leaf(BaseBlock* node);

    /**
     * @brief 显示复制选中的灯光效果
     */
    void showEffectLight(bool show, bool effectChild = true);
    bool isEffectLight();
    QPointF GetPos(){return QPointF(0,0);};

    void showItem(BaseBlock* node, bool show = true);

    void deleteItem(BaseBlock* node);

    BaseBlock* getRecursive();

signals:


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

protected:
    QGraphicsPixmapItem* m_pbackground;
    QGraphicsPixmapItem* m_picon;
private:
    /* 是否移动 */
    bool m_bMoved;
    /* 复制选中的灯光效果 */
    bool m_bShow;
    QPoint startPoint;
};

#endif // BASEBLOCK_H

