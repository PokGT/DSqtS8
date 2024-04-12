#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ouvrirImage(void);
    void SauvegarderImage(void);

    /**
     * @brief Cette méthode permet d’adapté limage a la taille de la fenêtre
     */
    void DimentionementImage(void);

    void ActualiserBarres(int width, int height);

private slots :
    void paintEvent(QPaintEvent *);

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QRect _Rect;
    QImage _Image;
    QRect _SelectionRect;

};
#endif // MAINWINDOW_H
