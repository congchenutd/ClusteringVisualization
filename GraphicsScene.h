#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "CellMap.h"

#include <QGraphicsScene>

typedef QList<int> Cluster;
typedef QList<Cluster> Clusters;

class ShapeItem;
class CellMapFileModel;

/**
 * A scene for showing cellmaps
 */
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = Q_NULLPTR);

    void setFileModel(CellMapFileModel*  model);

    void setClusters(const Clusters& clusters);
    void updateLayout(bool clustering = true);

private slots:
    void onItemSelected();

signals:
    void cellmapSelected(CellMap* cellmap);

private:
    CellMapFileModel* _fileModel;
};

#endif // GRAPHICSSCENE_H
