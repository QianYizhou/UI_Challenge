#ifndef MAINWIDGET_H
#define MAINWIDGET_H
/*#-------------------------------------------------
#
# Project created by liduoyou 2018-05-30T22:31:11
#
#-------------------------------------------------*/
#include <QWidget>
#include <QLabel>
#include "./uiwidgets/catalogselector.h"
#include "./uiwidgets/blockpalette.h"
//namespace Ui {
//class MainWidget;
//}
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif
class BlockPalette;
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void resizeEvent(QResizeEvent *event);
private:
//    Ui::MainWidget *ui;
    QLabel* m_pTitleBar;//名称bar
    QLabel* m_pBackground;//widget背景
    CatalogSelector* m_pCatalog;
    BlockPalette* m_pBlockPalette;
    QGraphicsView* m_pProjectView;
    QLabel* m_pModuleBackground;//单元背景
    QLabel* m_pScriptBackground;//模块集合背景
    QLabel* m_pSceneBackground;//场景背景
    void updateMyGeometry();
    void setupUI();
};

#endif // MAINWIDGET_H
