//
// Created by peter on 2022-08-16.
//

#ifndef CHIP_8_MAIN_WINDOW_H
#define CHIP_8_MAIN_WINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class main_window; }
QT_END_NAMESPACE

class main_window : public QMainWindow {
Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);

    ~main_window() override;

private:
    Ui::main_window *ui;
};


#endif //CHIP_8_MAIN_WINDOW_H
