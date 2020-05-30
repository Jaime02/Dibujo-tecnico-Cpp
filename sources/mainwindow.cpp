#include "headers/mainwindow.h"
#include "headers/renderer.h"
#include "headers/diedric.h"
#include <QtWidgets>

MainWindow::MainWindow(QApplication *main_event)
{
    this->setWindowTitle("Technical drawing");
    this->main_event = main_event;
    this->main_event->setStyle("Fusion");
    this->main_event->setWindowIcon(QIcon(":/Logo.ico"));

    QWidget *wc = new QWidget();
    this->setCentralWidget(wc);

    QMenuBar *menu_bar = new QMenuBar();

    QMenu *file_menu = menu_bar->addMenu("File");

    QAction *save_action = new QAction("Save");
    file_menu->addAction(save_action);

    // connect(accion_guardar, &QAction::triggered, this, &MainWindow::save_test);

    Renderer *renderer = new Renderer(this);
    renderer->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    this->dock_renderer.setWindowTitle("Renderer");
    this->dock_renderer.setWidget(renderer);
    this->dock_renderer.setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::LeftDockWidgetArea, &this->dock_renderer);

    QGraphicsScene scene;
    QGraphicsView graphics_view(&scene);
    Diedric diedric(this);
    diedric.setFocusPolicy(Qt::ClickFocus);
    diedric.setFixedSize(1000, 1000);
    scene.addWidget(&diedric);

    QDockWidget *dock_diedric = new QDockWidget("Diedric");
    dock_diedric->setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::RightDockWidgetArea, dock_diedric);
    dock_diedric->setWidget(&graphics_view);

    //  Zoom out

    QFont *font = new QFont("Arial");
    font->setPointSize(10);

    QStackedWidget *widget_stack = new QStackedWidget(wc);
    widget_stack->setGeometry(0, 90, 500, 470);

    QWidget *p1 = new QWidget();
    QWidget *p2 = new QWidget();

    widget_stack->addWidget(p1);
    widget_stack->addWidget(p2);

    QPushButton *button_change_tab = new QPushButton("Figures", p1);
    button_change_tab->setGeometry(400, 0, 70, 23);

    QPushButton *button_change_tab_2 = new QPushButton("Return", p2);
    button_change_tab_2->setGeometry(400, 0, 70, 23);

    QLabel *information = new QLabel("Information:", wc);
    information->setFont(*font);
    information->setGeometry(0, 10, 91, 16);

    QLabel *position = new QLabel("Position:", wc);
    position->setFont(*font);
    position->setGeometry(0, 30, 71, 16);

    QLabel *quadrant = new QLabel("First quadrant", wc);
    quadrant->setFont(*font);
    quadrant->setGeometry(60, 30, 151, 16);

    QLabel *vertical_angle = new QLabel(wc);
    vertical_angle->setFont(*font);
    vertical_angle->setGeometry(0, 50, 121, 16);

    QLabel *horizontal_angle = new QLabel(wc);
    horizontal_angle->setFont(*font);
    horizontal_angle->setGeometry(120, 50, 130, 16);

    QLabel *view = new QLabel("View:", wc);
    view->setFont(*font);
    view->setGeometry(0, 71, 91, 16);

    QPushButton *button_reset = new QPushButton("Reset (R)", wc);
    button_reset->setGeometry(0, 90, 81, 23);
    QPushButton *button_front = new QPushButton("Front (1) ''", wc);
    button_front->setGeometry(90, 90, 81, 23);
    QPushButton *button_top = new QPushButton("Top (2) '", wc);
    button_top->setGeometry(180, 90, 81, 23);
    QPushButton *button_side = new QPushButton("Side (3) '''", wc);
    button_side->setGeometry(270, 90, 81, 23);

    QLabel *create_points = new QLabel("Create points:", p1);
    create_points->setGeometry(0, 30, 91, 16);
    QLabel *x_distance = new QLabel("X coord", p1);
    x_distance->setGeometry(0, 50, 91, 16);
    QLabel *y_distance = new QLabel("Y coord", p1);
    y_distance->setGeometry(0, 70, 91, 16);
    QLabel *z_distance = new QLabel("Z coord", p1);
    z_distance->setGeometry(0, 90, 91, 16);

    QLineEdit *point_name = new QLineEdit(p1);
    point_name->setGeometry(0, 115, 151, 25);
    point_name->setPlaceholderText("Point name");

    QPushButton *point_button = new QPushButton("Create");
    point_button->setGeometry(0, 142, 151, 22);

    QSpinBox *x_spinbox = new QSpinBox();
    x_spinbox->setGeometry(100, 50, 51, 20);
    x_spinbox->setRange(-499, 499);
    QSpinBox *y_spinbox = new QSpinBox();
    y_spinbox->setGeometry(100, 70, 51, 20);
    y_spinbox->setRange(-499, 499);
    QSpinBox *z_spinbox = new QSpinBox();
    z_spinbox->setGeometry(100, 90, 51, 20);
    z_spinbox->setRange(-499, 499);

    this->showMaximized();
    this->setMenuBar(menu_bar);
};

MainWindow::~MainWindow(){
};
