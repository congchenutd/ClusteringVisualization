#ifndef CELLMAPFILEMODEL_H
#define CELLMAPFILEMODEL_H

#include <QString>
#include "CellMap.h"
#include "GraphicsScene.h"

/**
 * A model representing a cellmap (.json) file
 */
class CellMapFileModel
{
public:
    void setFilePath(const QString& filePath);
    CellMap* getCellMap(int id) const;
    QList<Cluster> getCellMaps() const;
    void save();

private:
    QString  _filePath;
    CellMaps _cellmaps;
};

#endif // CELLMAPFILEMODEL_H
