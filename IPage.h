#ifndef IPAGE_H
#define IPAGE_H

#include <QWidget>

class IPage: public QWidget
{
public:
    IPage(QWidget* parent = 0);
    virtual ~IPage();

    virtual void reload() = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
};

#endif // IPAGE_H
