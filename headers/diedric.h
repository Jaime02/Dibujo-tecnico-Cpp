#pragma once
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Diedric : public QWidget
{
    Q_OBJECT
    QMainWindow *parent;

public:
    Diedric(QMainWindow *parent);
};

