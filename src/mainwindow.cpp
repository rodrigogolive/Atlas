#include <QGraphicsView>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    resize(1024, 768);

    m_scene = new Scene();
    m_view = new QGraphicsView(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view);

    m_view->setScene(m_scene);
}

MainWindow::~MainWindow()
{
}

