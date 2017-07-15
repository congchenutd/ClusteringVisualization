#include "GraphicsScene.h"
#include "ShapeItem.h"
#include "CellMapFileModel.h"

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene (parent)
{
    connect(this, &GraphicsScene::selectionChanged, this, &GraphicsScene::onItemSelected);
}

void GraphicsScene::setFileModel(CellMapFileModel* model) {
    _fileModel = model;
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
            auto item = new ShapeItem(_fileModel->getCellMap(id));
            addItem(item);
            item->setPos(x + item->boundingRect().width() / 2, y);
            x += item->boundingRect().width() + space;
        }
    }
}

void GraphicsScene::onItemSelected()
{
    auto selected = selectedItems();
    if (selected.isEmpty())
        emit cellmapSelected(0);
    else
        emit cellmapSelected(static_cast<ShapeItem*>(selected.front())->getCellMap());
}
