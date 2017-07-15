#ifndef CELLMAPMODEL_H
#define CELLMAPMODEL_H

#include <QStandardItemModel>

class CellMap;

class CellMapModel : public QStandardItemModel
{
public:
    CellMapModel(QObject* parent = Q_NULLPTR);


    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);


    void setCellMap(CellMap* cellmap);

private:
    CellMap* _cellmap;

    enum {ID, TemplateID, RowCount, ColumnCount, DateTime, Values};
};

#endif // CELLMAPMODEL_H
