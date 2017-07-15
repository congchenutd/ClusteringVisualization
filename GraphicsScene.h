#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "CellMap.h"

#include <QGraphicsScene>

typedef QList<int> Cluster;

class ShapeItem;
class CellMapFileModel;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = Q_NULLPTR);

    void setFileModel(CellMapFileModel* model);
    void setClusters(const QList<Cluster>& clusters);

private slots:
    void onItemSelected();

signals:
    void cellmapSelected(CellMap* cellmap);

private:
    CellMapFileModel* _fileModel;
};

#endif // GRAPHICSSCENE_H
