#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include "ui_PageWidget.h"
#include "GraphicsScene.h"
#include "IPage.h"
#include "CellMapModel.h"
#include "CellMapFileModel.h"
#include <QFileSystemModel>
#include <QStandardItemModel>

class ShapeItem;

class PageWidget : public IPage
{
    Q_OBJECT

public:
    explicit PageWidget(QWidget* parent = 0);

    void zoomIn();
    void zoomOut();

protected:
    virtual void fileClicked(const QModelIndex& idx);
    virtual void cellmapClicked(CellMap* cellmap);

private slots:
    void onFileClicked(const QModelIndex& idx);
    void onCellMapSelected(CellMap* cellmap);

protected:
    Ui::PageWidget ui;

    QFileSystemModel    _fsModel;
    GraphicsScene       _scene;
    CellMapModel        _cellmapModel;
    CellMapFileModel    _fileModel;
};

#endif // PAGEWIDGET_H
