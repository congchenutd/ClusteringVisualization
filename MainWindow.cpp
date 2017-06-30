#include "MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.splitter->setSizes(QList<int>() << 100 << 800);

    _model.setRootPath(QDir::currentPath());
    _model.setResolveSymlinks(false);
    _model.setNameFilterDisables(false);
    _model.setFilter(QDir::Files);
    _model.setNameFilters(QStringList() << "*.json");

    ui.listView->setModel(&_model);
    ui.listView->setRootIndex(_model.index(QDir::currentPath()));

    connect(ui.listView, &QListView::clicked, this, &MainWindow::onFileClicked);

    ui.graphicsView->setScene(&_scene);
}

void MainWindow::onFileClicked(const QModelIndex& idx)
{
    // load cellmaps
    auto cellmapFilePath = _model.data(idx).toString();
    QFile cellmapsFile(cellmapFilePath);
    if (!cellmapsFile.open(QFile::ReadOnly))
        return;

    _scene.setCellMaps(CellMap::fromJson(cellmapsFile.readAll()));

    // load clusters
    QFileInfo fileInfo(cellmapFilePath);
    auto clustersFilePath = fileInfo.path() + QDir::separator() + fileInfo.baseName() + ".clusters";
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

    _scene.setClusters(clusters);
    _scene.setSceneRect(_scene.itemsBoundingRect());
    ui.graphicsView->setSceneRect(_scene.sceneRect().adjusted(-50, -50, 100, 100));
}
