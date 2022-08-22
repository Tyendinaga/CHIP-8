#pragma once

#include <QMainWindow>
#include <emulator.hpp>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    void BootGame();

    void Play();
    void Pause();

    // Emulator
    std::unique_ptr<emulator> emu;
};
