#include "CellMapFileModel.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

CellMapFileModel::CellMapFileModel()
{

}

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
