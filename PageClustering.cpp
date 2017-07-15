#include "PageClustering.h"

PageClustering::PageClustering(QWidget* parent)
    : PageWidget (parent)
{

}

void PageClustering::reload()
{
    _fsModel.setRootPath("");
    _fsModel.setRootPath(QDir::currentPath());
    _fsModel.setResolveSymlinks(false);
    _fsModel.setNameFilterDisables(false);
    _fsModel.setFilter(QDir::Files);
    _fsModel.setNameFilters(QStringList() << "*.clusters");
}

void PageClustering::fileClicked(const QModelIndex& idx)
{
    // load clusters
    auto clustersFilePath = _fsModel.data(idx).toString();
    QFile clustersFile(clustersFilePath);
    if (!clustersFile.open(QFile::ReadOnly))
        return;

    QList<Cluster> clusters;
    QString fileContent = clustersFile.readAll();
    QRegularExpression rx("\\[(\\d+(,\\s*\\d+)*)\\]");
    auto it = rx.globalMatch(fileContent);
    while (it.hasNext())
    {
        auto match = it.next();
        Cluster cluster;
        foreach (auto id, match.captured(1).split(", ", QString::SkipEmptyParts))
            cluster << id.toInt();
        clusters << cluster;
    }

    // reload cellmaps
    QFileInfo fileInfo(clustersFilePath);
    auto baseName = fileInfo.baseName();
    if (baseName.contains("-"))
        baseName = baseName.split("-").first().simplified();
    auto cellmapFilePath = fileInfo.path() + QDir::separator() + baseName + ".json";
    _fileModel.setFilePath(cellmapFilePath);

    _scene.setFileModel(&_fileModel);
    _scene.setClusters(clusters);
    _scene.setSceneRect(_scene.itemsBoundingRect());
    ui.graphicsView->setSceneRect(_scene.sceneRect().adjusted(-50, -50, 100, 100));
    ui.graphicsView->zoomActual();
}
