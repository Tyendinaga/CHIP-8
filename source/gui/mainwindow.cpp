#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <iostream>
#include <emulator.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    // Instantiate Emulator
    emu = std::make_unique<emulator>();

    // No Idea what this actually does.
    ui->setupUi(this);

    // Trigger About QT Popup on Click
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);

    // Exit Application on Selection of Exit
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::closeAllWindows);

    //
    connect(ui->actionBoot_Game, &QAction::triggered, this, &MainWindow::BootGame);

    //
    connect(ui->actionBoot_Test, &QAction::triggered, this, &MainWindow::BootTest);

    //
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::Play);

    //
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::Pause);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::BootGame() {
    std::cout << "Test boot";
    emu->Boot("PONG.C8");
}

void MainWindow::BootTest() {
    std::cout << "Test boot";
    emu->Boot("TEST_OPCODE.C8");
}

void MainWindow::Play() {
    emu->Play();
}

void MainWindow::Pause() {
    emu->Pause();
}


