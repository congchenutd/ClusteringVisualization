#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include "CellMap.h"

#include <QGraphicsItem>

/**
 * An item representing a cellmap
 */
class ShapeItem : public QGraphicsItem
{
public:
    ShapeItem(CellMap* cellmap, QGraphicsItem* parent = Q_NULLPTR);

    QRectF contentRect() const;
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    CellMap* getCellMap() const;

private:
    CellMap* _cellmap;

    static QList<QColor> _colors;

public:
    static const int CellSize = 5;  // cell's width in pixel
};

#endif // SHAPEITEM_H
