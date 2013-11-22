#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    resize(1024, 768);

    m_scene = new Scene();
    m_view = new QGraphicsView(this);

    // buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(10, 10, 10, 10);

    QPushButton *openImage = new QPushButton(tr("Add image(s)"));
    connect(openImage, SIGNAL(released()), this, SLOT(openDialog()));
    buttonsLayout->addWidget(openImage);

    QPushButton *saveImage = new QPushButton(tr("Save image"));
    connect(saveImage, SIGNAL(released()), this, SLOT(saveDialog()));
    buttonsLayout->addWidget(saveImage);

    // main scene
    QVBoxLayout *mainViewLayout = new QVBoxLayout(this);
    mainViewLayout->setContentsMargins(0, 0, 0, 0);
    mainViewLayout->addLayout(buttonsLayout);
    mainViewLayout->addWidget(m_view);

    m_view->setScene(m_scene);
    m_scene->drawInformationsLayer(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openDialog()
{
    QString filter = tr("Images") + QString(" (*.png *.jpg)");
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Add image(s)"), QDir::homePath(), filter);

    m_scene->addImages(files);
}

void MainWindow::saveDialog()
{
    QString filter = tr("Images") + QString(" (*.png *.jpg)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"), QDir::homePath(), filter);

    m_scene->saveImage(fileName);
}
