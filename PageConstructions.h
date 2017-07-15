#ifndef PAGECONSTRUCTIONS_H
#define PAGECONSTRUCTIONS_H

#include "PageWidget.h"
#include "ui_PageConstructions.h"

class PageConstructions : public PageWidget
{
    Q_OBJECT

public:
    explicit PageConstructions(QWidget* parent = 0);

    void reload();
    void zoomIn();
    void zoomOut();

private:
    Ui::PageConstructions ui;
};

#endif // PAGECONSTRUCTIONS_H
