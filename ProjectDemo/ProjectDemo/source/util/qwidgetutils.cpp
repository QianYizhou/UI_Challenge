#include "qwidgetutils.h"
#include "../Blocks/baseblock.h"
BlockRanderView::BlockRanderView()
    :QGraphicsView(new QGraphicsScene())
{
    this->scene()->setSceneRect(0, 0, 1000, 1000);
    this->setGeometry(QRect(0, 0, 1000, 1000));
}

BlockRanderView::~BlockRanderView()
{

}

namespace QWidgetUtils {

    void setBackgroundColor(QWidget* p_pWidget, QColor p_Color)
    {
        QPalette pal(p_pWidget->palette());
        pal.setColor(QPalette::Background, p_Color);
        p_pWidget->setAutoFillBackground(true);
        p_pWidget->setPalette(pal);
    }

    void setTextColor(QWidget* p_pWidget, QColor p_Color)
    {
        QPalette pal(p_pWidget->palette());
        pal.setColor(QPalette::WindowText, p_Color);
        p_pWidget->setPalette(pal);

    }


    QString ButtonIconStyleSheet(QString p_ObjectName,QString p_NormalImage, QString p_HoverImage, QString p_PressedImage)
    {
        QString l_styleSheet = QString("QPushButton#%4{border-image: url(%1);} QPushButton#%4:hover{border-image: url(%2);} QPushButton#%4:pressed{border-image: url(%3);}")
                .arg(p_NormalImage)
                .arg(p_HoverImage)
                .arg(p_PressedImage)
                .arg(p_ObjectName);

        return l_styleSheet;
    }

    QPixmap* readPixmap(QGraphicsItem* p_pGraphicesItem, QGraphicsView* p_pGraphicsView)
    {
        QSizeF size = p_pGraphicesItem->boundingRect().size();

        QPixmap* pixmap = new QPixmap(size.width(), size.height());

        pixmap->fill(QColor::fromRgb(0,0,0, 0));

        QPainter   painter(pixmap);

        QPointF pos = p_pGraphicsView->mapFromScene(p_pGraphicesItem->pos());
        QRect m_rect(pos.x(), pos.y(), size.width(), size.height());
        QRect m_tragetRect(0,0, size.width(), size.height());

        p_pGraphicsView->render(&painter, m_tragetRect, m_rect);

        return pixmap;
    }

    QPixmap* readBlockPixmap(BaseBlock* p_pBlock, QGraphicsView* p_pGraphicsView)
    {
        QSizeF size = p_pBlock->boundingRect().size();

        QPixmap* pixmap = new QPixmap(size.width(), size.height());

        pixmap->fill(QColor::fromRgb(0,0,0, 0));

        QPainter   painter(pixmap);

        QPointF pos = p_pGraphicsView->mapFromScene(p_pBlock->pos());
        QRect m_rect(pos.x(), pos.y(), size.width(), size.height());
        QRect m_tragetRect(0,0, size.width(), size.height());

        p_pGraphicsView->render(&painter, m_tragetRect, m_rect);

        return pixmap;
    }


    QPixmap* readBlockPixmap2(BaseBlock* p_pBlock, QMatrix p_matrix)
    {
        static BlockRanderView randerView;
        randerView.hide();
        randerView.setMatrix(p_matrix);

        QSizeF size = p_pBlock->boundingRect().size();

        QPointF sizeTmp = p_matrix.map(QPointF(size.width(), size.height()));

        size = QSizeF(sizeTmp.x(), sizeTmp.y());

        QPixmap* pixmap = new QPixmap(size.width() + 10, size.height() + 10);

        pixmap->fill(QColor::fromRgb(0,0,0, 0));

        QPainter   painter(pixmap);

        BaseBlock* newBlock = p_pBlock;// p_pBlock->copy();
        //newBlock->setPos(5,5);

        randerView.scene()->addItem(newBlock);

        QPointF pos = randerView.mapFromScene(p_pBlock->pos());
        QRect m_rect(pos.x() - 5, pos.y() - 5, size.width() + 10, size.height() + 10);
        QRect m_tragetRect(0,0, size.width() + 10, size.height() + 10);

        randerView.render(&painter, m_tragetRect, m_rect);

        randerView.scene()->removeItem(newBlock);

        //randerView.scene()->clear();

        return pixmap;
    }

}




