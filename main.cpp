#include "widget.hpp"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget mainWindow;
    mainWindow.show();

    return app.exec();
}
