#include "MainWindow.h"
#include <QApplication>

// workaround for a bug on Mavericks
// Finder returns / as the working path of an app bundle
// but if the app is run from terminal, the path is correct
// This method calcluates the path of the bundle from the application's path
QString getCurrentPath()
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    return dir.absolutePath();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef Q_OS_OSX
    QDir::setCurrent(getCurrentPath());
#endif

    MainWindow window;
    window.showMaximized();

    return app.exec();
}
