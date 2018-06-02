#ifndef QWIDGETUTILS_H
#define QWIDGETUTILS_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QGraphicsView>
#include "../Blocks/baseblock.h"
class BlockRanderView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BlockRanderView();
    virtual ~BlockRanderView();

signals:
public slots:
};

namespace QWidgetUtils {

    void setBackgroundColor(QWidget* p_pWidget, QColor p_Color);

    void setTextColor(QWidget* p_pWidget, QColor p_Color);

    QString ButtonIconStyleSheet(QString p_ObjectName, QString p_NormalImage, QString p_HoverImage, QString p_PressedImage);

    QPixmap* readPixmap(QGraphicsItem* p_pGraphicesItem, QGraphicsView* p_pGraphicsView);

    QPixmap* readBlockPixmap(BaseBlock* p_pBlock, QGraphicsView* p_pGraphicsView);

    QPixmap* readBlockPixmap2(BaseBlock* p_pBlock, QMatrix p_matrix);

}



#endif // QWIDGETUTILS_H
