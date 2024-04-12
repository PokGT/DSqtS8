#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _SelectionRect = QRect(100, 100, 200, 150);

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
        Painter.drawRect(_SelectionRect);
    }
}

void MainWindow::ouvrirImage(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png)");
    if (!fileName.isEmpty()) {

        _Image.size();
        _Image = QImage(fileName);
        DimentionementImage();
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

void MainWindow::DimentionementImage(void)
{
    QSize dimention = _Image.size();
    if(dimention.height()>600)
    {
        int newHeight = 600;
        _Image = _Image.scaledToHeight(newHeight, Qt::SmoothTransformation);
        this->resize(QSize(_Image.size().width(),600));
        update();
    }
}

void MainWindow::SauvegarderImage(void)
{
    if (!_Image.isNull()) {
        QImage selectedImage = _Image.copy(_SelectionRect);
        QString savePath = QFileDialog::getSaveFileName(this, tr("Sauvegarde Sous Image"), "", tr("Image Files (*.png)"));
        if (!savePath.isEmpty()) {
            if (!selectedImage.isNull()) {
                if (!selectedImage.save(savePath)) {
                    QMessageBox::critical(this, tr("Erreur"), tr("Erreur lore de la Sauvegarde!"));
                }
            } else {
                QMessageBox::critical(this, tr("Erreur"), tr("pas de selection !"));
            }
        }
    }
}
