#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dark->setChecked(false);
    ui->light->setChecked(true);
    ui->leDisplay->setReadOnly(true);

    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->btnPlusMinus, SIGNAL(clicked()), this, SLOT(do_operation()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(do_operation()));
    connect(ui->btn1DelNaX, SIGNAL(clicked()), this, SLOT(do_operation()));

    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(do_math_operation()));
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(do_math_operation()));
    connect(ui->btnDelen, SIGNAL(clicked()), this, SLOT(do_math_operation()));
    connect(ui->btnUmn, SIGNAL(clicked()), this, SLOT(do_math_operation()));
    connect(ui->btnStep, SIGNAL(clicked()), this, SLOT(do_math_operation()));
    connect(ui->btnPercent, SIGNAL(clicked()), this, SLOT(do_math_operation()));

    ui->btnPlus->setCheckable(true);
    ui->btnMinus->setCheckable(true);
    ui->btnDelen->setCheckable(true);
    ui->btnUmn->setCheckable(true);
    ui->btnStep->setCheckable(true);
    ui->btnPercent->setCheckable(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dark_triggered()
{   
    if(ui->dark->isChecked())
    {
        ui->dark->setChecked(true);
        ui->light->setChecked(false);
    }
    else
    {
        ui->dark->setChecked(false);
        ui->light->setChecked(true);
    }

    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
}


void MainWindow::on_light_triggered()
{
    ui->dark->setChecked(false);
    ui->light->setChecked(true);

    qApp->setPalette(style()->standardPalette());
}


double numFirst;


void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton*)sender();

    double allNumbers;
    QString Res;

    if (ui->leDisplay->text().contains(".") && button->text() == "0")
    {
        Res =  ui->leDisplay->text() + button->text();
    }
    else
    {
        allNumbers = (ui->leDisplay->text() + button->text()).toDouble();
        Res = QString::number(allNumbers, 'g', 15);
    }
    ui->leDisplay->setText(Res);
}


void MainWindow::on_btnZap_clicked()
{
    if(!(ui->leDisplay->text().contains('.')))
    {
        ui->leDisplay->setText(ui->leDisplay->text() + ".");
    }
}


void MainWindow::do_operation()
{
    QPushButton *button = (QPushButton*)sender();
    double allNumbers;
    QString Res;

    allNumbers = (ui->leDisplay->text()).toDouble();

    if(button->text() == "+/-")
    {
        allNumbers *= -1;
        Res = QString::number(allNumbers, 'g', 15);
    }
    else if(button->text() == "sqrt")
    {
        if (ui->leDisplay->text().toDouble() < 0.0)
        {
            ui->leDisplay->setText("Error");
            return;
        }
        Res = QString::number(std::sqrt(allNumbers), 'g', 15);
    }
    else if(button->text() == "1/x")
    {
        if (allNumbers == 0.0)
        {
            ui->leDisplay->setText("inf");
            return;
        }
        allNumbers = 1.0 / allNumbers;
        Res = QString::number(allNumbers, 'g', 15);
    }
    ui->leDisplay->setText(Res);
}


void MainWindow::do_math_operation()
{
    QPushButton *button = (QPushButton*)sender();
    numFirst = ui->leDisplay->text().toDouble();
    ui->leDisplay->setText("");
    button->setChecked(true);
}


void MainWindow::on_btnAC_clicked()
{
    ui->btnDelen->setChecked(false);
    ui->btnUmn->setChecked(false);
    ui->btnMinus->setChecked(false);
    ui->btnPlus->setChecked(false);
    ui->leDisplay->setText("0");
}


void MainWindow::on_btnRavno_clicked()
{
    double displayNumber, numSecond;
    QString result;
    numSecond = ui->leDisplay->text().toDouble();
    if(ui->btnPlus->isChecked())
    {
        displayNumber = numFirst + numSecond;
        result = QString::number(displayNumber, 'g', 15);
        ui->leDisplay->setText(result);
        ui->btnPlus->setChecked(false);
    }
    else if(ui->btnMinus->isChecked())
    {
        displayNumber = numFirst - numSecond;
        result = QString::number(displayNumber, 'g', 15);
        ui->leDisplay->setText(result);
        ui->btnMinus->setChecked(false);
    }
    else if(ui->btnUmn->isChecked())
    {
        displayNumber = numFirst * numSecond;
        result = QString::number(displayNumber, 'g', 15);
        ui->leDisplay->setText(result);
        ui->btnUmn->setChecked(false);
    }
    else if(ui->btnDelen->isChecked())
    {
        if(numSecond == 0)
        {
            ui->leDisplay->setText("inf");
            return;
        }
        else
        {
            displayNumber = numFirst / numSecond;
            result = QString::number(displayNumber, 'g', 15);
            ui->leDisplay->setText(result);
        }
        ui->btnDelen->setChecked(false);
    }
    else if(ui->btnStep->isChecked())
    {
        displayNumber = std::pow(numFirst, numSecond);
        result = QString::number(displayNumber, 'g', 15);
        ui->leDisplay->setText(result);
        ui->btnStep->setChecked(false);
    }
    else if(ui->btnPercent->isChecked())
    {
        displayNumber = numFirst * 0.01 * numSecond;
        result = QString::number(displayNumber, 'g', 15);
        ui->leDisplay->setText(result);
        ui->btnPercent->setChecked(false);
    }
}


void MainWindow::on_btnBackspace_clicked()
{
    if (ui->leDisplay->text() == "0")
    {
        return;
    }
    QString text = ui->leDisplay->text();
    text.chop(1);
    if (text.isEmpty())
    {
        text = "0";
    }
    ui->leDisplay->setText(text);
}


double memory;


void MainWindow::on_btnMPlus_clicked()
{
    MainWindow::on_btnRavno_clicked();
    memory += ui->leDisplay->text().toDouble();
}


void MainWindow::on_btnMMinus_clicked()
{
    MainWindow::on_btnRavno_clicked();
    memory -= ui->leDisplay->text().toDouble();
}


void MainWindow::on_btnMC_clicked()
{
    memory = 0.0;
}


void MainWindow::on_btnMR_clicked()
{
    ui->leDisplay->setText(QString::number(memory));
}


void MainWindow::on_btnMS_clicked()
{
    MainWindow::on_btnRavno_clicked();
    memory = ui->leDisplay->text().toDouble();
}

