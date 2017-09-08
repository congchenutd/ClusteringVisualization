#ifndef CELLMAP_H
#define CELLMAP_H

#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QVector>

class CellMap;
typedef QMap<int, CellMap*> CellMaps;

class CellMap
{
public:
    CellMap();
    CellMap(int id, int nRows, int nCols);
    CellMap (const CellMap& another);

    int getID() const;
    void setID(int id);

    int getTemplateID() const;
    void setTemplateID(int templateID);

    int rowCount()    const;
    int columnCount() const;

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime& dateTime);

    int getClusterID() const;
    void setClusterID(int cluster);

    QString getValues() const;                  // values to a 1d comma-separated String

    QVector<int>& operator[] (int index);

    static CellMap*  fromJson(const QJsonObject& jsonObj);
    static CellMaps  fromJson(const QByteArray&  byteArray);
    QJsonObject toJson() const;

private:
    int                     _id;
    int                     _templateID;
    QDateTime               _dateTime;
    int                     _clusterID;
    QVector<QVector<int>>   _array;     // 2d array
};

#endif // CELLMAP_H
