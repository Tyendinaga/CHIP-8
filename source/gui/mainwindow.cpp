#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

}

MainWindow::~MainWindow() {
    delete ui;
}
