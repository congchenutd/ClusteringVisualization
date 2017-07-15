#include "CellMap.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

CellMap::CellMap()
    : _id(-1),
      _templateID (-1)
{}

CellMap::CellMap(int id, int nRows, int nCols)
    : _id (id),
      _templateID (-1),
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

int CellMap::getTemplateID() const {
    return _templateID;
}

void CellMap::setTemplateID(int templateID) {
    _templateID = templateID;
}

int CellMap::rowCount() const {
    return _array.length();
}

int CellMap::columnCount() const {
    return _array.isEmpty() ? 0 : _array[0].length();
}

QDateTime CellMap::getDateTime() const {
    return _dateTime;
}

void CellMap::setDateTime(const QDateTime& dateTime) {
    _dateTime = dateTime;
}

QString CellMap::getValues() const
{
    QStringList result;
    for (int row = 0; row < rowCount(); ++row)
        for (int col = 0; col < columnCount(); ++col)
            result.append(QString::number(_array[row][col]));
    return result.join(", ");
}

QVector<int>& CellMap::operator[](int index) {
    return _array[index];
}

CellMap* CellMap::fromJson(const QJsonObject& jsonObj)
{
    // meta info
    QDateTime dateTime = QDateTime::fromString(jsonObj.value("datetime").toString(), "yyyy-MM-dd HH:mm:ss");

    QJsonObject cellmapJsonObj = jsonObj.value("cellmap").toObject();
    int id      = cellmapJsonObj.value("id").toInt();
    int nRows   = cellmapJsonObj.value("nRows").toInt();
    int nCols   = cellmapJsonObj.value("nCols").toInt();
    CellMap* cellmap = new CellMap(id, nRows, nCols);
    cellmap->setDateTime(dateTime);
    if (cellmapJsonObj.contains("templateid"))
        cellmap->setTemplateID(cellmapJsonObj.value("templateid").toInt());

    // values
    QJsonArray values = cellmapJsonObj.value("values").toArray();
    int row = 0;
    int col = 0;
    foreach (auto value, values)
    {
        (*cellmap)[nRows - row - 1][col++] = value.toInt();
        if (col == nCols)
        {
            row ++;
            col = 0;
        }
    }

    return cellmap;
}

CellMaps CellMap::fromJson(const QByteArray& byteArray)
{
    CellMaps result;
    QJsonArray jsonArray = QJsonDocument::fromJson(byteArray).array();
    foreach (auto jsonValue, jsonArray)
    {
        auto cellmap = CellMap::fromJson(jsonValue.toObject());
        result.insert(cellmap->getID(), cellmap);
    }
    return result;
}

QJsonObject CellMap::toJson() const
{
    QJsonObject result;
    result.insert("datetime", getDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    QJsonObject cellmapJsonObj;
    cellmapJsonObj.insert("id",         getID());
    cellmapJsonObj.insert("nRows",      rowCount());
    cellmapJsonObj.insert("nCols",      columnCount());
    cellmapJsonObj.insert("templateid", getTemplateID());
    QJsonArray array;
    for (int row = 0; row < rowCount(); ++row)
        for (int col = 0; col < columnCount(); ++col)
            array.append(_array[row][col]);
    cellmapJsonObj.insert("values", array);
    result.insert("cellmap", cellmapJsonObj);
    return result;
}
