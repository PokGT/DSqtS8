#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _Painter =  new QPainter(this);

    connect(ui->action_ouvrir,&QAction::triggered,this,&MainWindow::ouvrirImage);
    connect(ui->actionSauvegarder_Image,&QAction::triggered,this,&MainWindow::SauvegarderImage);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_Painter != nullptr)
    {
        delete _Painter;
    }
    if(_Image != nullptr)
    {
        delete _Image;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!_Image->isNull())
    {
        _Painter->setPen(Qt::red);
        _Painter->drawImage(0,0,*_Image);
    }
}

void MainWindow::ouvrirImage(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png)");
    if (!fileName.isEmpty()) {

        if(_Image != nullptr){delete _Image;}
        _Image = new QImage(fileName);

        if (_Image->isNull()) {
            QMessageBox::critical(this, "Erreur", "Impossible de charger l'image.");
        } else {
            update();
        }
    } else {
        QMessageBox::information(this, "Information", "Aucune image sélectionnée.");
    }
}
void MainWindow::SauvegarderImage(void)
{
    qDebug() <<"cc 20";
}
