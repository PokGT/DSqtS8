#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->action_ouvrir,&QAction::triggered,this,&MainWindow::ouvrirImage);
    connect(ui->actionSauvegarder_Image,&QAction::triggered,this,&MainWindow::SauvegarderImage);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!_Image.isNull()){
        QPainter Painter(this);
        Painter.setPen(Qt::red);
        Painter.drawImage(0,0,_Image);
        Painter.drawRect(_Rect);
    }
}

void MainWindow::ouvrirImage(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png)");
    if (!fileName.isEmpty()) {

        _Image.size();

        _Image = QImage(fileName);
        //_Image.scaled(this->ui->centralwidget->width(), this->ui->centralwidget->height(), Qt::KeepAspectRatio);
        if (_Image.isNull()) {
            QMessageBox::critical(this, "Erreur", "Impossible de charger l'image.");
        } else {
            update();
        }
    } else {
        QMessageBox::information(this, "Information", "Aucune image sélectionnée.");
    }
    update();
}
void MainWindow::SauvegarderImage(void)
{
    qDebug() <<"cc 20";
}
