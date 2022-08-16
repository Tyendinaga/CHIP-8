//
// Created by peter on 2022-08-16.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
#include "ui_main_window.h"


main_window::main_window(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
}

main_window::~main_window() {
    delete ui;
}
