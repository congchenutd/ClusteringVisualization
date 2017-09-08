#include "ShapeItem.h"

#include <QPainter>

ShapeItem::ShapeItem(CellMap* cellmap, QGraphicsItem* parent)
    : QGraphicsItem (parent),
      _cellmap (cellmap)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

QList<QColor> ShapeItem::_colors = QList<QColor>()  << Qt::blue
                                                    << QColor(184, 134, 11) // brown
                                                    << Qt::cyan
                                                    << Qt::gray
                                                    << Qt::green
                                                    << QColor(255, 0, 255)  // magenta
                                                    << QColor(255, 165, 0)  // orange
                                                    << QColor(128, 0, 128)  // purple
                                                    << Qt::red
                                                    << Qt::yellow
                                                    << QColor(128, 0, 0)    // maroon
                                                    << Qt::black;

QRectF ShapeItem::boundingRect() const
{
    const int PenWidth = 4;
    return contentRect().adjusted(-PenWidth/2, -PenWidth/2, PenWidth/2, PenWidth/2);
}

void ShapeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::transparent);
    painter->drawRect(contentRect());

    painter->setPen(Qt::transparent);
    auto bottomLeft = contentRect().bottomLeft();
    for (int row = 0; row < _cellmap->rowCount(); ++row)
        for (int col = 0; col < _cellmap->columnCount(); ++col)
        {
            int x = static_cast<int>(bottomLeft.x()) + CellSize * col;
            int y = static_cast<int>(bottomLeft.y()) - CellSize * (row + 1);
            auto colorID = (*_cellmap)[row][col];
            if (colorID > -1)
            {
                painter->setBrush(_colors[colorID]);
                painter->drawRect(x, y, CellSize, CellSize);
            }
        }

    if (this->isSelected())
    {
        painter->setBrush(Qt::transparent);
        painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

CellMap* ShapeItem::getCellMap() const {
    return _cellmap;
}

QRectF ShapeItem::contentRect() const
{
    const int width  = CellSize * _cellmap->columnCount();
    const int height = CellSize * _cellmap->rowCount();
    return QRectF(- width / 2, - height / 2, width, height);
}
