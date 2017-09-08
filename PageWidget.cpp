#include "PageWidget.h"
#include "ShapeItem.h"

PageWidget::PageWidget(QWidget *parent) :
    IPage (parent)
{
    ui.setupUi(this);
    ui.splitter->setSizes(QList<int>() << 150 << 800 << 150);

    ui.listView->setModel(&_fsModel);
    ui.listView->setRootIndex(_fsModel.index(QDir::currentPath()));

    _scene.setFileModel(&_fileModel);

    ui.graphicsView->setScene(&_scene);
    ui.tableView->setModel(&_cellmapModel);

    connect(ui.listView,    &QListView::clicked,                this, &PageWidget::onFileClicked);
    connect(&_scene,        &GraphicsScene::cellmapSelected,    this, &PageWidget::onCellMapSelected);
    connect(&_cellmapModel, &CellMapModel::dataSubmitted,       this, &PageWidget::onCellMapModified);
}

void PageWidget::zoomIn() {
    ui.graphicsView->zoomIn();
}

void PageWidget::zoomOut() {
    ui.graphicsView->zoomOut();
}

void PageWidget::fileClicked(const QModelIndex& idx) {
    Q_UNUSED(idx)
}

void PageWidget::cellmapClicked(CellMap* cellmap) {
    Q_UNUSED(cellmap);
}

void PageWidget::onFileClicked(const QModelIndex& idx) {
    fileClicked(idx);
}

void PageWidget::onCellMapSelected(CellMap* cellmap)
{
    if (cellmap != 0)
    {
        _cellmapModel.setCellMap(cellmap);
        ui.tableView->resizeRowsToContents();
    }
}

void PageWidget::onCellMapModified() {
    _fileModel.save();
    _scene.updateLayout();
}
