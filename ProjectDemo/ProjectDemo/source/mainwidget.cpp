#include "mainwidget.h"
//#include "ui_mainwidget.h"

#include <QApplication>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

#include "widgetcompanent/frameless_helper.h"
#include "./uiwidgets/projectview.h"
extern float g_fScale;
extern qreal factor;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int WINDOWRectWidth;
extern int WINDOWRectHeight;
ProjectView* m_pCurrentProjectView;
#define SCREEN_WIDTH QApplication::primaryScreen()->availableSize().width()
#define SCREEN_HEIGHT QApplication::primaryScreen()->availableSize().height()

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
//  , ui(new Ui::MainWidget)
  , m_pTitleBar(NULL)
  , m_pBackground(NULL)
  , m_pModuleBackground(NULL)
  , m_pScriptBackground(NULL)
  , m_pSceneBackground(NULL)
{
//    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setupUI();
    this->setMinimumSize(SCREEN_WIDTH * 0.7, SCREEN_HEIGHT * 0.7);
    this->setMaximumSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(m_pTitleBar->height());  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放
}

MainWidget::~MainWidget()
{
//    delete ui;
    SAFE_DELETE(m_pSceneBackground);
    SAFE_DELETE(m_pScriptBackground);
    SAFE_DELETE(m_pModuleBackground);

    SAFE_DELETE(m_pBackground);
    SAFE_DELETE(m_pTitleBar);
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<" Widget::resizeEvent this->width() = "<<this->size()<<"oldsize = "<<event->oldSize();

    g_fScale = factor*1/QApplication::primaryScreen()->devicePixelRatio();
    g_fScaleX = (qreal)((qreal)factor*this->size().width()/(qreal)SCREEN_WIDTH);
    g_fScaleY = (qreal)((qreal)factor*this->size().height()/(qreal)SCREEN_HEIGHT);
//    qDebug()<<"g_fScale = "<<g_fScale<<g_fScaleX<<g_fScaleY;

    updateMyGeometry();
}

void MainWidget::updateMyGeometry()
{
//    this->adjustSize();
//    m_pBackground->setGeometry(0,0,this->size().width(),this->size().height());
//    m_pTitleBar->setGeometry(0,0,this->size().width(),40);
    this->move((SCREEN_WIDTH - this->size().width())/2, (SCREEN_HEIGHT - this->size().height())/2);
}

void MainWidget::setupUI()
{
    //初始化UI
    m_pTitleBar = new QLabel();
    m_pTitleBar->setObjectName("m_pTitleBar");
    m_pTitleBar->setStyleSheet("QLabel#m_pTitleBar{background-color:#434343;}");
    m_pBackground = new QLabel();
    m_pBackground->setObjectName("m_pBackground");
    m_pBackground->setStyleSheet("QLabel#m_pBackground{background-color:#fdfdfd;}");
    m_pModuleBackground = new QLabel();
    m_pModuleBackground->setObjectName("m_pModuleBackground");
    m_pModuleBackground->setStyleSheet("QLabel#m_pModuleBackground{background-color:#979797;}");
    m_pCatalog = new CatalogSelector(this);
    m_pBlockPalette = new BlockPalette(this);
    m_pProjectView = new ProjectView(new QGraphicsScene,this);
    m_pScriptBackground = new QLabel();
    m_pScriptBackground->setObjectName("m_pScriptBackground");
    m_pScriptBackground->setStyleSheet("QLabel#m_pScriptBackground{background-color:#97fdfd;}");
    m_pSceneBackground = new QLabel();
    m_pSceneBackground->setObjectName("m_pSceneBackground");
    m_pSceneBackground->setStyleSheet("QLabel#m_pSceneBackground{background-color:#00fda6;}");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0,0,0,0);
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);
    vLayout->addWidget(m_pTitleBar,40);

    hLayout->addWidget(m_pCatalog,SCREEN_WIDTH/20);
    hLayout->addWidget(m_pBlockPalette,SCREEN_HEIGHT/5);
    hLayout->addWidget(m_pProjectView,SCREEN_HEIGHT*3/4);
    m_pCurrentProjectView = (ProjectView*)m_pProjectView;
//    hLayout->addWidget(m_pModuleBackground,SCREEN_WIDTH/20);
//    hLayout->addWidget(m_pScriptBackground,SCREEN_HEIGHT/5);
//    hLayout->addWidget(m_pSceneBackground,SCREEN_HEIGHT*3/4);

    vLayout->addLayout(hLayout,SCREEN_HEIGHT - 40);


    setLayout(vLayout);

    connect(m_pCatalog, SIGNAL(selectedItemChanged(int)),
            m_pBlockPalette, SLOT(onSelectedCatChanged(int)));

    connect(m_pBlockPalette, SIGNAL(currentCatChanged(int)),
            m_pCatalog, SLOT(onCurrentCatChanged(int)));
}
