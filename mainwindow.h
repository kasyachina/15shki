#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update();
    void updateTable();
    void updateMoves();
    void showTime();
    void resetTime();
private slots:
    void on_MainTable_cellClicked(int row, int column);

    void on_menu_newgame_triggered();

    void on_menu_restart_triggered();

    void on_menu_exit_triggered();

private:
    bool time_freezed;
    Ui::MainWindow *ui;
    QTableWidgetItem *SimpleItem = new QTableWidgetItem;
};
#endif // MAINWINDOW_H
