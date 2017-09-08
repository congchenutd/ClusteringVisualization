#include "MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    onCurrentTabChanged(ui.tabWidget->currentIndex());  // load default page

    connect(ui.tabWidget,       &QTabWidget::currentChanged,   this, &MainWindow::onCurrentTabChanged);
    connect(ui.actionLayout,    &QAction::triggered, this, &MainWindow::onLayout);
    connect(ui.actionZoomIn,    &QAction::triggered, this, &MainWindow::onZoomIn);
    connect(ui.actionZoomOut,   &QAction::triggered, this, &MainWindow::onZoomOut);
}

void MainWindow::onCurrentTabChanged(int index)
{
    _currentPage = static_cast<IPage*>(ui.tabWidget->widget(index));
    _currentPage->reload();
}

void MainWindow::onLayout() {
    _currentPage->autoLayout();
}

void MainWindow::onZoomIn() {
    _currentPage->zoomIn();
}

void MainWindow::onZoomOut() {
    _currentPage->zoomOut();
}
