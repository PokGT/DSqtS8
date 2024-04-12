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

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    int x1 = this->ui->horizontalSlider->value();
    int x2 = this->ui->horizontalSlider_2->value();
    int y1 = value;
    int y2= this->ui->verticalSlider_2->value();

    _SelectionRect.setRect(x1,y1,x2-x1,y2-y1);
    update();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int x1 = value;
    int x2 = this->ui->horizontalSlider_2->value();
    int y1 = this->ui->verticalSlider->value();
    int y2= this->ui->verticalSlider_2->value();

    _SelectionRect.setRect(x1,y1,x2-x1,y2-y1);
    update();
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    int x1 = this->ui->horizontalSlider->value();
    int x2 = value;
    int y1 = this->ui->verticalSlider->value();
    int y2= this->ui->verticalSlider_2->value();

    _Rect.setRect(x1,y1,x2-x1,y2-y1);
}


void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    int x1 = this->ui->horizontalSlider->value();
    int x2 = this->ui->horizontalSlider_2->value();
    int y1 = this->ui->verticalSlider->value();
    int y2= value;

    _SelectionRect.setRect(x1,y1,x2-x1,y2-y1);
    update();
}

void MainWindow::ActualiserBarres(int width, int height)
{
    //Actualiser le maximum
    this->ui->horizontalSlider->setMaximum(height);
    this->ui->horizontalSlider_2->setMaximum(height);
    this->ui->verticalSlider->setMaximum(width);
    this->ui->verticalSlider_2->setMaximum(width);
    //Actualiser la taille et la position
    this->ui->centralwidget->setMaximumWidth(width);
    this->ui->centralwidget->setMaximumHeight(height);
    this->ui->horizontalSlider->setMaximumWidth(width);
    this->ui->horizontalSlider_2->setMaximumWidth(width);
    this->ui->verticalSlider_2->setMaximumHeight(height);
    this->ui->verticalSlider_2->setMaximumHeight(height);
}
