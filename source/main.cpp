// Standard Libraries
#include <cstdlib>
#include <iostream>

// QT Stuff
#include <QtCore>
#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    //
    std::cout << "Qt Version: " << qVersion() << std::endl;

    //
    QApplication app(argc, argv);
    MainWindow qWindow;
    qWindow.show();
    app.exec();

    //
	return EXIT_SUCCESS;
}

