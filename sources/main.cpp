#include "headers/mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
	QApplication main_event{ argc, argv };
	MainWindow window{ &main_event };
	return main_event.exec();
}