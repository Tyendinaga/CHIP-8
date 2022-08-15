//
// Created by peter on 2022-08-14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TestWindow.h" resolved

#include "testwindow.h"
#include "ui_TestWindow.h"

TestWindow::TestWindow(QWidget *parent) : QWidget(parent), ui(new Ui::TestWindow) {
    ui->setupUi(this);
}

TestWindow::~TestWindow() {
    delete ui;
}
