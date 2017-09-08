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
    // load cellmaps: convert the cluster file path into a cellmap file path
    auto clustersFilePath = _fsModel.data(idx).toString();
    QFileInfo fileInfo(clustersFilePath);   // e.g., "dlee - free play.clusters"
    auto cellmapFilePath = fileInfo.path() + QDir::separator() + fileInfo.baseName() + ".json";    // "dlee - free play.json"

    _fileModel.setCellmapFilePath(cellmapFilePath);
    _fileModel.setClustersFilePath(clustersFilePath);

    // load clusters
    QFile clustersFile(clustersFilePath);
    if (!clustersFile.open(QFile::ReadOnly))
        return;

    _scene.updateLayout();
}
