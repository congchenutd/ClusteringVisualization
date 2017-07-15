#ifndef PAGECLUSTERING_H
#define PAGECLUSTERING_H

#include "PageWidget.h"

#include <QWidget>

class PageClustering : public PageWidget
{
public:
    PageClustering(QWidget* parent = 0);

    void reload();

protected:
    void fileClicked(const QModelIndex& idx);
};

#endif // PAGECLUSTERING_H
