#pragma once
#include <QtWidgets>
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
    QDockWidget dock_renderer;
};
