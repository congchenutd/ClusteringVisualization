#include "CellMapFileModel.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>
#include <QRegularExpression>

void CellMapFileModel::setCellmapFilePath(const QString& filePath)
{
//    if (!_filePath.isEmpty())
//        save();

    // load cellmaps
    _cellmapFilePath = filePath;
    QFile cellmapsFile(_cellmapFilePath);
    if (!cellmapsFile.open(QFile::ReadOnly))
        return;

    _cellmaps = CellMap::fromJson(cellmapsFile.readAll());
}

void CellMapFileModel::setClustersFilePath(const QString& filePath)
{
    // load clusters
    _clustersFilePath = filePath;

    QFile clustersFile(_clustersFilePath);
    if (!clustersFile.open(QFile::ReadOnly))
        return;

    QString fileContent = clustersFile.readAll();
    QRegularExpression rx("\\[(\\d+(,\\s*\\d+)*)\\]");
    auto it = rx.globalMatch(fileContent);
    int clusterID = 1;
    while (it.hasNext())
    {
        auto match = it.next();
        foreach (auto id, match.captured(1).split(", ", QString::SkipEmptyParts))
            if (auto cellmap = getCellMap(id.toInt()))
                cellmap->setClusterID(clusterID);
        clusterID++;
    }
}

CellMap* CellMapFileModel::getCellMap(int id) const {
    return _cellmaps.contains(id) ? _cellmaps.value(id) : 0;
}

/**
 * @return all cellmaps packed as a list of clusters, each cluster has one id
 */
Clusters CellMapFileModel::getCellMaps() const
{
    Clusters result;
    foreach (auto id, _cellmaps.keys())
        result << (Cluster() << id);
    return result;
}

Clusters CellMapFileModel::getClusters() const
{
    QMap<int, Cluster> clusters;
    foreach (auto cellmap, _cellmaps.values())
    {
        int clusterID = cellmap->getClusterID();
        if (clusterID > 0)
            clusters[clusterID].append(cellmap->getID());
    }
    return clusters.values();
}

// Save the cellmaps back to file
void CellMapFileModel::save()
{
    QJsonArray jsonArray;
    foreach (auto cellmap, _cellmaps.values())
        jsonArray.append(cellmap->toJson());

    QFile cellMapFile(_cellmapFilePath);
    if (cellMapFile.open(QFile::WriteOnly))
    {
        QTextStream os(&cellMapFile);
        QJsonDocument jsonDoc(jsonArray);
        os << jsonDoc.toJson();
    }

    QFile clustersFile(_clustersFilePath);
    if (clustersFile.open(QFile::WriteOnly))
    {
        QTextStream os(&clustersFile);
        foreach (auto cluster, getClusters())
        {
            if (!cluster.isEmpty())
            {
                os << "[";
                QStringList cellmapList;
                foreach (auto cellmapID, cluster)
                    cellmapList << QString::number(cellmapID);
                os << cellmapList.join(", ");
                os << "]" << endl;
            }
        }
    }
}
