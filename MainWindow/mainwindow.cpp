#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    setAutoFillBackground(true);


    m_widget = new MainWidget;
    setCentralWidget(m_widget);
}

MainWindow::~MainWindow()
{
}

