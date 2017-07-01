#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GraphicsScene.h"
#include "ui_MainWindow.h"

#include <QFileSystemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private slots:
    void onReload();
    void onFileClicked(const QModelIndex& idx);

private:
    Ui::MainWindow ui;

    QFileSystemModel    _model;
    GraphicsScene       _scene;
};

#endif // MAINWINDOW_H
