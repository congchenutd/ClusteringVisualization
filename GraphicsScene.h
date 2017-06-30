#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "CellMap.h"

#include <QGraphicsScene>

typedef QList<int> Cluster;

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = Q_NULLPTR);

    void setCellMaps(const QMap<int, CellMap>& cellmaps);
    void setClusters(const QList<Cluster>& clusters);

private:
    QMap<int, CellMap> _cellmaps;
};

#endif // GRAPHICSSCENE_H
