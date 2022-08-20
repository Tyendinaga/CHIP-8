#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // No Idea what this actually does.
    ui->setupUi(this);


    // Trigger About QT Popup on Click
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

MainWindow::~MainWindow() {
    delete ui;
}
