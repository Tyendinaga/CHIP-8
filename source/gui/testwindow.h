#pragma once


#include <QWidget>


namespace Ui
{
    class TestWindow;
}

class TestWindow : public QWidget
{

public:
    explicit TestWindow(QWidget *parent = nullptr);

    ~TestWindow() override;

private:
    Ui::TestWindow *ui;
};
