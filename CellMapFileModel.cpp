#include "CellMapFileModel.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

void CellMapFileModel::setFilePath(const QString& filePath)
{
    if (!_filePath.isEmpty())
        save();

    _filePath = filePath;
    QFile cellmapsFile(_filePath);
    if (!cellmapsFile.open(QFile::ReadOnly))
        return;

    _cellmaps = CellMap::fromJson(cellmapsFile.readAll());
}

CellMap* CellMapFileModel::getCellMap(int id) const {
    return _cellmaps.value(id);
}

/**
 * @return all cellmaps packed as a list of clusters, each cluster has one id
 */
QList<Cluster> CellMapFileModel::getCellMaps() const
{
    QList<Cluster> result;
    foreach (auto id, _cellmaps.keys())
        result << (Cluster() << id);
    return result;
}

// Save the cellmaps back to file
void CellMapFileModel::save()
{
    QJsonArray jsonArray;
    foreach (auto cellmap, _cellmaps.values())
        jsonArray.append(cellmap->toJson());

    QFile file(_filePath);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream os(&file);
        QJsonDocument jsonDoc(jsonArray);
        os << jsonDoc.toJson();
    }
}
