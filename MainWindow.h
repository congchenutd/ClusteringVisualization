#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

class IPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private slots:
    void onCurrentTabChanged(int index);
    void onReload();
    void onZoomIn();
    void onZoomOut();

private:
    Ui::MainWindow ui;

    IPage*  _currentPage;
};

#endif // MAINWINDOW_H
