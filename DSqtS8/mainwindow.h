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

private slots :
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QRect _Rect;
    QImage _Image;
    QRect _SelectionRect;

};
#endif // MAINWINDOW_H
