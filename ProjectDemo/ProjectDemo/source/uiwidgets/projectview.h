#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H
#include <QGraphicsView>
#include "../Blocks/baseblock.h"
#include "../Blocks/displayblock.h"
class ProjectView : public QGraphicsView
{
    Q_OBJECT
public:
    ProjectView(QGraphicsScene * scene, QWidget * parent = 0);
    ~ProjectView();
    void ViewInit();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void dropEvent(QDropEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
private:
    DisplayBlock* m_pMain;
    BaseBlock* m_pRoot;
    QPoint m_PressPos;
    bool isPress;
    bool isctrl;
    bool isalt;
    //    void getSelectBlcok(QPoint pressPos, QPoint releasePos);
    void resetSystemSelectedStatus();
    void scaleScene(int offset, qreal width, qreal height);
};

#endif // PROJECTVIEW_H
