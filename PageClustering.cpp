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

    // only .clusters, corresponding .json file will be loaded when .clusters is clicked
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

    // load cellmaps
    QFileInfo fileInfo(clustersFilePath);   // e.g., "carl - free play.clusters"
    auto baseName = fileInfo.baseName();
    if (baseName.contains("-"))
        baseName = baseName.split("-").first().simplified();    // "carl"
    auto cellmapFilePath = fileInfo.path() + QDir::separator() + baseName + ".json";    // "carl.json"
    _fileModel.setFilePath(cellmapFilePath);

    _scene.setClusters(clusters);
    _scene.setSceneRect(_scene.itemsBoundingRect());
    ui.graphicsView->setSceneRect(_scene.sceneRect().adjusted(-50, -50, 100, 100));
    ui.graphicsView->zoomActual();
}
