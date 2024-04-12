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


        _Image = QImage(fileName);

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
    if (!currentImage.isNull()) {
        QImage selectedImage = currentImage.copy(selectionRect);
        QString savePath = QFileDialog::getSaveFileName(this, tr("Save Selection"), "", tr("Image Files (*.png)"));
        if (!savePath.isEmpty()) {
            if (!selectedImage.isNull()) {
                if (!selectedImage.save(savePath)) {
                    QMessageBox::critical(this, tr("Error"), tr("Failed to save selection!"));
                }
            } else {
                QMessageBox::critical(this, tr("Error"), tr("No selection to save!"));
            }
        }
    }
}
