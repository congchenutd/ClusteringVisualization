#include "GraphicsScene.h"
#include "ShapeItem.h"
#include "CellMapFileModel.h"
#include "GraphicsView.h"

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene (parent)
{
    connect(this, &GraphicsScene::selectionChanged, this, &GraphicsScene::onItemSelected);
}

void GraphicsScene::setFileModel(CellMapFileModel* model) {
    _fileModel = model;
}

void GraphicsScene::setClusters(const Clusters& clusters)
{
    clear();

    const int nRows     = 24;
    const int height    = ShapeItem::CellSize * nRows;
    const int space     = 20;

    // Create ShapeItems and place them on the scene one cluster a row
    int row = 0;
    foreach (auto cluster, clusters)
    {
        int x = 0;
        int y = (height + space) * row++;
        foreach (auto id, cluster)
        {
            auto cellmap = _fileModel->getCellMap(id);
            auto item = new ShapeItem(cellmap);
            addItem(item);
            item->setPos(x + item->boundingRect().width() / 2, y);
            x += item->boundingRect().width() + space;
        }
    }
}

void GraphicsScene::updateLayout(bool clustering)
{
    if (clustering)
        setClusters(_fileModel->getClusters());
    else
        setClusters(_fileModel->getCellMaps());

    setSceneRect(itemsBoundingRect());
    auto view = static_cast<GraphicsView*>(views().front());
    view->setSceneRect(sceneRect().adjusted(-50, -50, 100, 100));
    view->zoomActual();
}

void GraphicsScene::onItemSelected()
{
    auto selected = selectedItems();
    if (selected.isEmpty())
        emit cellmapSelected(0);
    else
        emit cellmapSelected(static_cast<ShapeItem*>(selected.front())->getCellMap());
}
