#include "CellMap.h"
#include "CellMapModel.h"

CellMapModel::CellMapModel(QObject* parent)
    : QStandardItemModel (parent),
      _cellmap (0)
{
    setColumnCount(1);
    setHeaderData(0, Qt::Horizontal, tr("Value"));
    setRowCount(Count);
    setHeaderData(ID,           Qt::Vertical, tr("ID"));
    setHeaderData(TemplateID,   Qt::Vertical, tr("Template ID"));
    setHeaderData(RowCount,     Qt::Vertical, tr("Row count"));
    setHeaderData(ColumnCount,  Qt::Vertical, tr("Column count"));
    setHeaderData(DateTime,     Qt::Vertical, tr("Date time"));
    setHeaderData(ClusterID,      Qt::Vertical, tr("Cluster ID"));
    setHeaderData(Values,       Qt::Vertical, tr("Values"));
}

QVariant CellMapModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole && _cellmap != 0) {
        switch (index.row())
        {
        case ID:
            return _cellmap->getID();
        case TemplateID:
            return _cellmap->getTemplateID();
        case RowCount:
            return _cellmap->rowCount();
        case ColumnCount:
            return _cellmap->columnCount();
        case DateTime:
            return _cellmap->getDateTime();
        case ClusterID:
            return _cellmap->getClusterID();
        case Values:
            return _cellmap->getValues();
        }
    }

    return QStandardItemModel::data(index, role);
}

bool CellMapModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    bool result = QStandardItemModel::setData(index, value, role);
    if (result)
    {
        if (index.row() == TemplateID)
        {
            _cellmap->setTemplateID(value.toInt());
            emit dataSubmitted();
        }
        else if (index.row() == ClusterID)
        {
            _cellmap->setClusterID(value.toInt());
            emit dataSubmitted();
        }
    }
    return result;
}

void CellMapModel::setCellMap(CellMap* cellmap) {
    _cellmap = cellmap;
    emit dataChanged(index(ID, 0), index(Values, 0));
}
