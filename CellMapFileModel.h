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
    void setCellmapFilePath (const QString& filePath);
    void setClustersFilePath(const QString& filePath);

    CellMap* getCellMap(int id) const;
    Clusters getCellMaps() const;

    Clusters getClusters() const;

    void save();

private:
    QString     _cellmapFilePath;
    QString     _clustersFilePath;
    CellMaps    _cellmaps;
};

#endif // CELLMAPFILEMODEL_H
