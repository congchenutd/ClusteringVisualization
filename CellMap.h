#ifndef CELLMAP_H
#define CELLMAP_H

#include <QJsonObject>
#include <QMap>
#include <QVector>

class CellMap
{
public:
    CellMap();
    CellMap(int id, int nRows, int nCols);
    CellMap (const CellMap& another);

    int getID() const;
    void setID(int id);

    int rowCount()    const;
    int columnCount() const;

    QVector<int>& operator[] (int index);

    static CellMap fromJson(const QJsonObject& jsonObj);
    static QMap<int, CellMap> fromJson(const QByteArray& byteArray);

private:
    int _id;
    QVector<QVector<int>> _array;
};

#endif // CELLMAP_H
