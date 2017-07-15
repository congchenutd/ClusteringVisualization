#ifndef CELLMAPFILEMODEL_H
#define CELLMAPFILEMODEL_H

#include <QString>
#include "CellMap.h"

class CellMapFileModel
{
public:
    CellMapFileModel();

    void setFilePath(const QString& filePath);
    CellMap* getCellMap(int id) const;
    void save();

private:
    QString  _filePath;
    CellMaps _cellmaps;
};

#endif // CELLMAPFILEMODEL_H
