#pragma once


#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class TestWindow; }
QT_END_NAMESPACE

class TestWindow : public QWidget {
Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);

    ~TestWindow() override;

private:
    Ui::TestWindow *ui;
};
