#include "GraphicsScene.h"
#include "ShapeItem.h"

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene (parent)
{
}

void GraphicsScene::setCellMaps(const QMap<int, CellMap>& cellmaps) {
    _cellmaps = cellmaps;
}

void GraphicsScene::setClusters(const QList<Cluster>& clusters)
{
    clear();

    const int nRows     = 24;
    const int height    = ShapeItem::CellSize * nRows;
    const int space     = 20;

    int row = 0;
    foreach (auto cluster, clusters)
    {
        int x = 0;
        int y = (height + space) * row++;
        foreach (auto id, cluster)
        {
            auto item = new ShapeItem(_cellmaps[id]);
            addItem(item);
            item->setPos(x + item->boundingRect().width() / 2, y);
            x += item->boundingRect().width() + space;
        }
    }
}
