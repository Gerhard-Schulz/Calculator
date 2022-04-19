#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dark_triggered();
    void on_light_triggered();
    void digits_numbers();
    void on_btnZap_clicked();
    void do_operation();
    void do_math_operation();
    void on_btnRavno_clicked();
    void on_btnAC_clicked();

    void on_btnBackspace_clicked();

    void on_btnMPlus_clicked();

    void on_btnMMinus_clicked();

    void on_btnMC_clicked();

    void on_btnMR_clicked();

    void on_btnMS_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
