#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_listview = new MenuListview;
}

MainWindow::~MainWindow()
{
}

