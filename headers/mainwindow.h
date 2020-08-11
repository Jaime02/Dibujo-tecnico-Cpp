#pragma once
#include <QtWidgets>
#include <QApplication>
#include <QObject>

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QApplication* main_event;

public:
	MainWindow(QApplication* main_event);
	~MainWindow();
};
