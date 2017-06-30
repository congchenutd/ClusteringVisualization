#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include "CellMap.h"

#include <QGraphicsItem>

class ShapeItem : public QGraphicsItem
{
public:
    ShapeItem(const CellMap& cellmap, QGraphicsItem* parent = Q_NULLPTR);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    CellMap _cellmap;

    static QList<QColor> _colors;

public:
    static const int CellSize = 5;
};

#endif // SHAPEITEM_H
