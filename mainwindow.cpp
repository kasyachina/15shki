#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table_content.h"
#include <QMessageBox>
#include <QTimer>

table_content t;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update();
    resetTime();
    time_freezed = false;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    timer -> start(1000);
}

void MainWindow::update()
{
    updateTable();
    updateMoves();
}
void MainWindow::resetTime()
{
    ui -> clock -> setText("00:00");
}
void MainWindow::showTime()
{
    if(!time_freezed)
    {
        int minutes = t.GetTime() / 60;
        auto f = [](int x)
        {
            QString ans = QString::number(x);
            if(x < 10)
            {
                return QString("0" + ans);
            }
            return ans;
        };
        ui -> clock -> setText(f(minutes) + ":" + f(t.GetTime()% 60));
        t.UpdateTime();
    }
}
void MainWindow::updateTable()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            QTableWidgetItem *it = new QTableWidgetItem;
            int number = t.GetItem(i, j);
            if(number != 0)
                it -> setText(QString::number(number));
            it -> setTextAlignment(Qt::AlignCenter);
            ui -> MainTable -> setItem(i, j, it);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateMoves()
{
    ui -> moves -> setText(QString("Ходы : ") + QString::number(t.GetMoves()));
}
void MainWindow::on_MainTable_cellClicked(int row, int column)
{
    t.MoveCell(row, column, t.GetPossibleMovement(row, column));
    update();
    if(t.IsFinished())
    {
        time_freezed = 1;
        if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            QApplication::quit();
        else {
            time_freezed = 0;
            t.MakeTable();
            update();
        }
    }
}

void MainWindow::on_menu_newgame_triggered()
{
    resetTime();
    t.MakeTable();
    update();
}

void MainWindow::on_menu_restart_triggered()
{
    resetTime();
    t.RestoreContents();
    update();
}

void MainWindow::on_menu_exit_triggered()
{
    QApplication::quit();
}
