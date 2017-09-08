#ifndef CELLMAPMODEL_H
#define CELLMAPMODEL_H

#include <QStandardItemModel>

class CellMap;

/**
 * A model for a cellmap
 */
class CellMapModel : public QStandardItemModel
{
    Q_OBJECT

public:
    CellMapModel(QObject* parent = Q_NULLPTR);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

    void setCellMap(CellMap* cellmap);

signals:
    void dataSubmitted();

private:
    CellMap* _cellmap;

    enum {ID, TemplateID, RowCount, ColumnCount, DateTime, ClusterID, Values, Count};
};

#endif // CELLMAPMODEL_H
