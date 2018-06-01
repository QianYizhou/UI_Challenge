#ifndef BLOCKBUILDER_H
#define BLOCKBUILDER_H

#include <QObject>
#include "baseblock.h"

class BlockBuilder : public QObject
{
    Q_OBJECT
public:
    explicit BlockBuilder(QGraphicsView* p_pProjectView, QObject *parent = 0);
    ~BlockBuilder();

    BaseBlock* create(int p_ID, int p_PosX, int p_PosY, float p_Zoom);

private:

    QGraphicsView* m_pProjectView;

signals:

public slots:


};

#endif // BLOCKBUILDER_H
