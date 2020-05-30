#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QApplication *main_event;

public:
    MainWindow(QApplication *main_event);
    ~MainWindow();
    void save_test();
};
