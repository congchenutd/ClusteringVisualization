#include "PageConstructions.h"

PageConstructions::PageConstructions(QWidget* parent) :
    PageWidget (parent)
{
}

void PageConstructions::reload()
{
    _fsModel.setRootPath("");
    _fsModel.setRootPath(QDir::currentPath());
    _fsModel.setResolveSymlinks(false);
    _fsModel.setNameFilterDisables(false);
    _fsModel.setFilter(QDir::Files);
    _fsModel.setNameFilters(QStringList() << "*.json");
}

void PageConstructions::fileClicked(const QModelIndex& idx)
{
    auto filePath = _fsModel.data(idx).toString();
    _fileModel.setCellmapFilePath(filePath);

    _scene.updateLayout(false);
}
