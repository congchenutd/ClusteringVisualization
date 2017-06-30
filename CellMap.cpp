#include "CellMap.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

CellMap::CellMap() {}

CellMap::CellMap(int id, int nRows, int nCols)
    : _id (id),
      _array(nRows, QVector<int>(nCols))
{}

CellMap::CellMap(const CellMap& another)
{
    _id     = another.getID();
    _array  = another._array;
}

int CellMap::getID() const {
    return _id;
}

void CellMap::setID(int id) {
    _id = id;
}

int CellMap::rowCount() const {
    return _array.length();
}

int CellMap::columnCount() const {
    return _array.isEmpty() ? 0 : _array[0].length();
}

QVector<int>& CellMap::operator[](int index)
{
    return _array[index];
}

CellMap CellMap::fromJson(const QJsonObject& jsonObj)
{
    // meta info
    int id      = jsonObj.value("id").toInt();
    int nRows   = jsonObj.value("nRows").toInt();
    int nCols   = jsonObj.value("nCols").toInt();

    // values
    CellMap cellmap(id, nRows, nCols);
    QJsonArray values = jsonObj.value("values").toArray();
    int row = 0;
    int col = 0;
    foreach (auto element, values)
    {
        cellmap[nRows - row - 1][col++] = element.toInt();
        if (col == nCols)
        {
            row ++;
            col = 0;
        }
    }

    return cellmap;
}

QMap<int, CellMap> CellMap::fromJson(const QByteArray& byteArray)
{
    QMap<int, CellMap> result;
    QJsonArray jsonArray = QJsonDocument::fromJson(byteArray).array();
    foreach (auto jsonValue, jsonArray)
    {
        auto jsonObj = jsonValue.toObject();
        if (jsonObj.value("status").toString() == "end")
        {
            auto jsonCellmap = jsonObj.value("cellMap").toObject();
            auto cellmap = CellMap::fromJson(jsonCellmap);
            result.insert(cellmap.getID(), cellmap);
        }
    }
    return result;
}
