#include "catalogselector.h"

#include <QFontMetrics>
#include "../define.h"
#include "../util/qsizepolicywidget.h"
#include "../util/css.h"

#define Item_max_height 80

int clamp(int p_value, int p_min, int p_max)
{
    p_value = (p_value < p_min) ? p_min : p_value;
    p_value = (p_value > p_max) ? p_max : p_value;

    return p_value;
}

QFont CatalogItem::s_defaultFont;

CatalogItem::CatalogItem(int p_catId, QString p_Icon, QString p_BgImage, QWidget *parent)
: QPushButton(parent)
, m_catId(p_catId)
, m_Icon(p_Icon)
, m_BgImage(p_BgImage)
{
    this->setCheckable(true);
    this->setObjectName("CatalogItem");
    QString bgStyle = QString("QPushButton#CatalogItem::checked{border-image: url(%1);}").arg(p_BgImage);
    bgStyle.append("QPushButton#CatalogItem{border-image: url(:/images/res/images/none.png);}");
    this->setStyleSheet(bgStyle);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onButtonClicked(bool)));

    QWidget* l_pBackground = new QWidget(this);

    QVBoxLayout* l_pVBoxLayout = new QVBoxLayout(this);

    QWidget* l_pIconWidget = new QWidget(this);
    l_pIconWidget->setObjectName("l_pIconWidget");
    QString iconStyle = QString("QWidget#l_pIconWidget{border-image: url(%1);}").arg(p_Icon);
    l_pIconWidget->setStyleSheet(iconStyle);

    QSizePolicyWidget* sizer = new QSizePolicyWidget(this);
    sizer->setMinimumSize(28,28);
    sizer->setChildWidget(l_pIconWidget);

    l_pVBoxLayout->addWidget(sizer, 3);

    m_pNameLabel = new  QLabel(this);
    QFont font = CSS::font();
    font.setPixelSize(12);
    s_defaultFont = font;
    m_pNameLabel->setFont(font);
    m_pNameLabel->setAlignment(Qt::AlignCenter);
    m_pNameLabel->setText(getModuleNameByID());
    m_pNameLabel->setWordWrap(true);
    m_pNameLabel->setStyleSheet(CSS::fontStyleSheet("#434343", s_defaultFont.pixelSize()));

    l_pVBoxLayout->addWidget(m_pNameLabel, 1);

//    l_pVBoxLayout->addStretch(1);

    l_pBackground->setLayout(l_pVBoxLayout);

    QVBoxLayout* l_pRootLayout = new QVBoxLayout(this);
    l_pRootLayout->setSpacing(0);
    l_pRootLayout->setMargin(0);

    l_pRootLayout->addWidget(l_pBackground,Item_max_height);

    QWidget* l_pSeparator = new QWidget(this);
    l_pSeparator->setMaximumHeight(3);
    l_pSeparator->setObjectName("l_pSeparator");
    l_pSeparator->setStyleSheet("QWidget#l_pSeparator{border-image: url(:/block_catalog/res/images/block_catalog/item_separater.png);}");
    l_pRootLayout->addWidget(l_pSeparator,3);

    this->setLayout(l_pRootLayout);
}

CatalogItem::~CatalogItem()
{

}

void CatalogItem::onButtonClicked(bool checked)
{
    this->setChecked(checked);
}

QString CatalogItem::getModuleNameByID()
{
    QString name = "";
    switch (m_catId) {
    case MODULELIB_CONTROLER:
        name = "运动";
        break;
    case MODULELIB_SENSOR:
        name = "检测";
        break;
    case MODULELIB_COMMAND:
        name = "控制语句";
        break;
    case MODULELIB_VAR:
        name = "变量";
        break;
    default:
        break;
    }
    return name;
}

void CatalogItem::setChecked(bool p_checked, bool emitevent)
{
    QPushButton::setChecked(p_checked);

    if(emitevent)
    {
        emit buttonClicked(p_checked);
    }
}

void CatalogItem::updateFontSize(QFont& p_Font)
{
    m_pNameLabel->setFont(p_Font);
    m_pNameLabel->setStyleSheet(CSS::fontStyleSheet("#434343", p_Font.pixelSize()));
}

CatalogSelector::CatalogSelector(QWidget *parent)
    : QWidget(parent)
    , m_currentSelected(NULL)
{
    Initialize();
}

void CatalogSelector::Initialize()
{
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pBackground = new QWidget(this);
    m_pBackground->setObjectName("CatalogSelector-m_pBackground");
    m_pBackground->setStyleSheet("QWidget#CatalogSelector-m_pBackground{border-image: url(:/block_catalog/res/images/block_catalog/bg.png);}");

    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);

    vBoxLayout->addStretch(1);

    {
        CatalogItem* l_pItem = new CatalogItem(MODULELIB_CONTROLER,
                                               ":/block_catalog/res/images/block_catalog/item_motion.png",
                                               ":/block_catalog/res/images/block_catalog/item_bg_blue.png",
                                               this);
        l_pItem->setMaximumHeight(Item_max_height);
        connect(l_pItem, SIGNAL(buttonClicked(bool)), this, SLOT(onButtonClicked(bool)));
        m_catalogs.append(l_pItem);
        vBoxLayout->addWidget(l_pItem, 2);

    }
    {
        CatalogItem* l_pItem = new CatalogItem(MODULELIB_SENSOR,
                                               ":/block_catalog/res/images/block_catalog/item_sensor.png",
                                               ":/block_catalog/res/images/block_catalog/item_bg_yellow.png",
                                               this);
        l_pItem->setMaximumHeight(Item_max_height);
        connect(l_pItem, SIGNAL(buttonClicked(bool)), this, SLOT(onButtonClicked(bool)));
        m_catalogs.append(l_pItem);
        vBoxLayout->addWidget(l_pItem, 2);
    }
    {
        CatalogItem* l_pItem = new CatalogItem(MODULELIB_COMMAND ,
                                               ":/block_catalog/res/images/block_catalog/item_control.png",
                                               ":/block_catalog/res/images/block_catalog/item_bg_red.png",
                                               this);
        l_pItem->setMaximumHeight(Item_max_height);
        connect(l_pItem, SIGNAL(buttonClicked(bool)), this, SLOT(onButtonClicked(bool)));
        m_catalogs.append(l_pItem);
        vBoxLayout->addWidget(l_pItem, 2);
    }
    {
        CatalogItem* l_pItem = new CatalogItem(MODULELIB_VAR,
                                               ":/block_catalog/res/images/block_catalog/item_math.png",
                                               ":/block_catalog/res/images/block_catalog/item_bg_green.png",
                                               this);
        l_pItem->setMaximumHeight(Item_max_height);
        connect(l_pItem, SIGNAL(buttonClicked(bool)), this, SLOT(onButtonClicked(bool)));
        m_catalogs.append(l_pItem);
        vBoxLayout->addWidget(l_pItem, 2);

    }

    vBoxLayout->addStretch(9);

    m_pBackground->setLayout(vBoxLayout);
    m_pBackground->setGeometry(QRect(0,0, width(), height()));

    setSelected((CatalogItem*)this->m_catalogs.first());
}

void CatalogSelector::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_pBackground->setGeometry(QRect(0,0, width(), height()));

}

void CatalogSelector::onButtonClicked(bool checked)
{

    CatalogItem* l_pCurrent = (CatalogItem*) sender();

    setSelected(l_pCurrent);
}

void CatalogSelector::setSelected(CatalogItem* p_pCurrentSelected, bool emitevent)
{
    if(m_currentSelected == p_pCurrentSelected)
    {
        if(m_currentSelected)
        {
            m_currentSelected->setChecked(true, false);
        }

        return;
    }

    if(m_currentSelected)
    {
        m_currentSelected->setChecked(false, false);
    }

    m_currentSelected = p_pCurrentSelected;
    m_currentSelected->setChecked(true, false);

    if(emitevent)
    {
        int l_index = m_catalogs.indexOf(m_currentSelected);
        emit selectedItemChanged(l_index);
    }
}

void CatalogSelector::onCurrentCatChanged(int p_Index)
{
    if(p_Index >= 0 && p_Index < m_catalogs.size())
    {
        setSelected((CatalogItem*)m_catalogs[p_Index], false);
    }
}

void CatalogSelector::wheelEvent(QWheelEvent *event)
{
    int l_index = m_catalogs.indexOf(m_currentSelected);

    if(event->delta() > 0)
    {
        l_index -= 1;
    }
    else
    {
        l_index += 1;
    }
    l_index = clamp(l_index, 0, m_catalogs.size() - 1);

    setSelected((CatalogItem*)m_catalogs[l_index]);
}

void CatalogSelector::updateFontSize()
{
    int l_MaxNameWidth = 0;

    QStringList catalogNames;
    getCatalogNames(catalogNames);

    QFont font = CatalogItem::s_defaultFont;
    int fontSize = font.pixelSize();

    l_MaxNameWidth = getTextMaxWidth(font, catalogNames);

    while (l_MaxNameWidth > 80 && fontSize >= 10)
    {
        fontSize--;
        font.setPixelSize(fontSize);

        l_MaxNameWidth = getTextMaxWidth(font, catalogNames);
    }

    for(int index = 0; index < m_catalogs.size(); index++)
    {
        CatalogItem* l_pitem = (CatalogItem*)m_catalogs.at(index);

        l_pitem->updateFontSize(font);
    }
}

void CatalogSelector::getCatalogNames(QStringList& p_textList)
{

    p_textList.clear();
    for(int index = 0; index < m_catalogs.size(); index++)
    {
        CatalogItem* l_pitem = (CatalogItem*)m_catalogs.at(index);

        p_textList.append(l_pitem->name());
    }

}

int CatalogSelector::getTextMaxWidth(QFont& p_font, QStringList& textList)
{
    int l_MaxNameWidth = 0;
    QFontMetrics l_metrics(p_font);

    for(int index = 0; index < textList.size(); index++)
    {
        l_MaxNameWidth = qMax(l_MaxNameWidth, l_metrics.width(textList[index]));
    }

    return l_MaxNameWidth;
}
