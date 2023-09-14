#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cell.h>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <stdio.h>
#include <stdlib.h>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void temps();//controla el cronometre
    void posar_mines();//coloca les mines
    int mines_adjacents(int fila, int col);//conta el num de mines adjacents
    void mostrar_cell(int fila, int col);//mostra la cell clicada
    QString random_icona();//genera un icona d bandera random
    void reset();//tonra a començar
    void start();//crea tots els elements
    void mouse_response(int x,int y,char but);// que te que fer quan clica
    void buidar(int x, int y);//reseteja tots els elements
    void posar_flag(int x,int y);//posa bandera
    void posar_num_mines_adj();//posa el num de mines
    bool victoria();//comprova les condicions de victora
    void derrota();//s'executa quan es perd
    void mostrar_bombes(int x,int y);//mostra les bombes
    void start_crono();//inicia el cronometre
void Message();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString seg="000";
    Cell* Matriz_bombes[9][9];
    int num_bombes=0;
    bool estat_crnono=false;//si el cronometre para o segueix
};
#endif // MAINWINDOW_H
