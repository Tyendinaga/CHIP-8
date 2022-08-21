#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <iostream>
#include <emulator.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // No Idea what this actually does.
    ui->setupUi(this);

    // Trigger About QT Popup on Click
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);

    // Exit Application on Selection of Exit
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::closeAllWindows);

    //
    connect(ui->actionBoot_Game, &QAction::triggered, this, &MainWindow::BootGame);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::BootGame() {
    std::cout << "Test boot";

    std::unique_ptr<emulator> emu(new emulator());

    emu->Boot();

}
