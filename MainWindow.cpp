#include "MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    onCurrentTabChanged(ui.tabWidget->currentIndex());

    connect(ui.tabWidget,       &QTabWidget::currentChanged,   this, &MainWindow::onCurrentTabChanged);
    connect(ui.actionReload,    &QAction::triggered, this, &MainWindow::onReload);
    connect(ui.actionZoomIn,    &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui.actionZoomOut,   &QAction::triggered, this, &MainWindow::onZoomOut);
}

void MainWindow::onCurrentTabChanged(int index)
{
    _currentPage = static_cast<IPage*>(ui.tabWidget->widget(index));
    _currentPage->reload();
}

void MainWindow::onReload() {
    _currentPage->reload();
}

void MainWindow::onZoomIn() {
    _currentPage->zoomIn();
}

void MainWindow::onZoomOut() {
    _currentPage->zoomOut();
}
