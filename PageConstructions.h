#ifndef PAGECONSTRUCTIONS_H
#define PAGECONSTRUCTIONS_H

#include "PageWidget.h"

class PageConstructions : public PageWidget
{
    Q_OBJECT

public:
    explicit PageConstructions(QWidget* parent = 0);

    void reload();

protected:
    void fileClicked(const QModelIndex& idx);
};

#endif // PAGECONSTRUCTIONS_H
