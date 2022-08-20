#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // No Idea what this actually does.
    ui->setupUi(this);


    // Trigger About QT Popup on Click
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

    // Exit Application on Selection of Exit
    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);
}

MainWindow::~MainWindow() {
    delete ui;
}
