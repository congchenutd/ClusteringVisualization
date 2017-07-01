#include "MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.splitter->setSizes(QList<int>() << 150 << 800);

    onReload();
    ui.listView->setModel(&_model);
    ui.listView->setRootIndex(_model.index(QDir::currentPath()));

    connect(ui.actionReload,    &QAction::triggered, this, &MainWindow::onReload);
    connect(ui.actionZoomIn,    &QAction::triggered, ui.graphicsView, &GraphicsView::zoomIn);
    connect(ui.actionZoomOut,   &QAction::triggered, ui.graphicsView, &GraphicsView::zoomOut);
    connect(ui.listView,        &QListView::clicked, this, &MainWindow::onFileClicked);

    ui.graphicsView->setScene(&_scene);
}

void MainWindow::onReload()
{
    _model.setRootPath("");
    _model.setRootPath(QDir::currentPath());
    _model.setResolveSymlinks(false);
    _model.setNameFilterDisables(false);
    _model.setFilter(QDir::Files);
    _model.setNameFilters(QStringList() << "*.clusters");
}

void MainWindow::onFileClicked(const QModelIndex& idx)
{
    // load clusters
    auto clustersFilePath = _model.data(idx).toString();
    QFile clustersFile(clustersFilePath);
    if (!clustersFile.open(QFile::ReadOnly))
        return;

    QList<Cluster> clusters;
    QString fileContent = clustersFile.readAll();
    QRegularExpression rx("\\[(\\d+(,\\s*\\d+)*)\\]");
    auto it = rx.globalMatch(fileContent);
    while (it.hasNext())
    {
        auto match = it.next();
        Cluster cluster;
        foreach (auto id, match.captured(1).split(", ", QString::SkipEmptyParts))
            cluster << id.toInt();
        clusters << cluster;
    }

    // load cellmaps
    QFileInfo fileInfo(clustersFilePath);
    auto baseName = fileInfo.baseName();
    if (baseName.contains("-"))
        baseName = baseName.split("-").first().simplified();
    auto cellmapFilePath = fileInfo.path() + QDir::separator() + baseName + ".json";
    QFile cellmapsFile(cellmapFilePath);
    if (!cellmapsFile.open(QFile::ReadOnly))
        return;

    _scene.setCellMaps(CellMap::fromJson(cellmapsFile.readAll()));
    _scene.setClusters(clusters);
    _scene.setSceneRect(_scene.itemsBoundingRect());
    ui.graphicsView->setSceneRect(_scene.sceneRect().adjusted(-50, -50, 100, 100));
    ui.graphicsView->zoomActual();
}
