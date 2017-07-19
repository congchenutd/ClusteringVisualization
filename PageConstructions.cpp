#include "PageConstructions.h"

PageConstructions::PageConstructions(QWidget* parent) :
    PageWidget (parent)
{
}

void PageConstructions::reload()
{
    _fsModel.setRootPath("");
    _fsModel.setRootPath(QDir::currentPath());
    _fsModel.setResolveSymlinks(false);
    _fsModel.setNameFilterDisables(false);
    _fsModel.setFilter(QDir::Files);
    _fsModel.setNameFilters(QStringList() << "*.json");
}

void PageConstructions::fileClicked(const QModelIndex& idx)
{
    auto filePath = _fsModel.data(idx).toString();
    _fileModel.setFilePath(filePath);

    _scene.setClusters(_fileModel.getCellMaps());
    _scene.setSceneRect(_scene.itemsBoundingRect());
    ui.graphicsView->setSceneRect(_scene.sceneRect().adjusted(-50, -50, 100, 100));
    ui.graphicsView->zoomActual();
}
