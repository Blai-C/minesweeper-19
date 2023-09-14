#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(resource);
    QString styleSheet = QString("font-size:%111px;").arg(QApplication::font().pointSize());
    this->setStyleSheet(styleSheet);
    start();
}






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::temps(){

    int num = seg.toInt();
    num++;
    if (num<=999){
    if (num<=9){
        QString s = QString::number(num);
        seg="00"+s;
     // 2 zeros
    }
    else if(num<=99){
        QString s = QString::number(num);
        seg="0"+s;
        //1 zero
    }
    else if(num>=100){
        QString s = QString::number(num);
        seg=s;
        //0 zeros
    }
    ui->time->display(seg);
    }
    else{
        QIcon icon(":/Icons/timeout.png");// per si el temps passa de 999 segons
        ui->startbut->setIcon(icon);
        derrota();
    }

}
void MainWindow::posar_mines(){
    srand (time(NULL));// per que canviin els valors random
    int i=0;
    while(i<=9){
    int randomValue1 = qrand() % 9;
    int randomValue2 = qrand() % 9;
    if(Matriz_bombes[randomValue1][randomValue2]->getCont()!=-1){
        Matriz_bombes[randomValue1][randomValue2]->setCont(-1);
        i++;
        num_bombes++;
        //posar mina cell
    }
    }

}
int MainWindow::mines_adjacents(int fila, int col){// retorna el nombre de mines adjacents a la casella
    int cont=0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if (fila+i>=0&&fila+i<=8&&col+j>=0&&col+j<=8){
            if (Matriz_bombes[fila+i][col+j]->getCont()==-1){
            cont++;
            }}
        }
    }
    return cont;
}
void MainWindow::buidar(int x, int y){// buida les caselles adjacents
    if(Matriz_bombes[x][y]->getCont()==0){
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if (x+i>=0&&x+i<=8&&y+j>=0&&y+j<=8){
                if (Matriz_bombes[x+i][y+j]->getCont()!=-1&&// si no es bombai si no esta clicat
                    Matriz_bombes[x+i][y+j]->getClick()==false){
                    Matriz_bombes[x+i][y+j]->showCont();
                    Matriz_bombes[x+i][y+j]->setClick(true);
                    if (Matriz_bombes[x+i][y+j]->getCont()==0){// si es un altre buit repeteix
                        buidar(x+i,y+j);}

                }

}
        }
    }
    }
}


void MainWindow::mostrar_cell(int fila, int col){// que mostrar quan l'usuari fa click
    if (Matriz_bombes[fila][col]->getClick()==false){

 if (Matriz_bombes[fila][col]->getCont()==0){// si la casella és buida
         Matriz_bombes[fila][col]->showCont();
         Matriz_bombes[fila][col]->setClick(true);
         buidar(fila,col);
         //destapar


     }

 else if(Matriz_bombes[fila][col]->getCont()==-1){// si hi ha una mina

     Matriz_bombes[fila][col]->showCont();
     Matriz_bombes[fila][col]->setClick(true);

     mostrar_bombes(fila,col);
     derrota();

     //destapar
 }
 else {// quan la casella tingui un numero
     Matriz_bombes[fila][col]->showCont();
     Matriz_bombes[fila][col]->setClick(true);
     //destapar

 }
    }
}

QString MainWindow::random_icona(){// per assingar les icones a la bandera
    int numicona = qrand() % 5;
    QString icona= ":/Icons/"+QString::number(numicona)+".png";
    return icona;
}


void MainWindow::reset(){

    this->setStyleSheet("background-color: rgba(80, 255, 80, 1);");// reseteja el tema
    seg="000";// reset i stop del timer
    ui->time->display(seg);
    timer->stop();
    estat_crnono=false;
    for (int i=0;i<9;i++){// reset de cada cell
        for(int j=0;j<9;j++){
            Matriz_bombes[i][j]->Reset();
            Matriz_bombes[i][j]->setIcon(QIcon());
        }
    }
    posar_mines();
    posar_num_mines_adj();
    num_bombes=10;
    ui->cont_mines->display(num_bombes);
    QIcon icon(":/Icons/smile.png");
    ui->startbut->setIcon(icon);
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            Matriz_bombes[i][j]->blockSignals(false);
        }
    }

}

void MainWindow::mouse_response(int x,int y,char but){// x y son coordenades but es char R o L dreta/esquerre
    start_crono();
    if(but=='R'){// click dret
        posar_flag(x,y);
    }
    if(but=='L'){//click esquerre
        mostrar_cell(x,y);
    }
    if (victoria()==true){// check de victoria
        derrota();// funcio que para el joc
        Message();//Qmessage
    }
}
void MainWindow::posar_flag(int x,int y){// marca bandera
    if (Matriz_bombes[x][y]->getFlag()==false && Matriz_bombes[x][y]->getClick()==false){// si no hi ha bandera o esta clickat
    Matriz_bombes[x][y]->setFlag(true);
    Matriz_bombes[x][y]->setClick(true);
    Matriz_bombes[x][y]->setIcond(random_icona());//posa icono
    QIcon icon(Matriz_bombes[x][y]->getIcon());
    Matriz_bombes[x][y]->setIcon(icon);
    num_bombes--;// redueix el contador de bombes
    ui->cont_mines->display(num_bombes);
    }
    else if (Matriz_bombes[x][y]->getFlag()==true){// treu bandera
        Matriz_bombes[x][y]->setFlag(false);
        Matriz_bombes[x][y]->setClick(false);
        Matriz_bombes[x][y]->setIcon(QIcon());
        num_bombes++;
        ui->cont_mines->display(num_bombes);
    }

}

void MainWindow::start(){// Inicialitza el joc

    this->setStyleSheet("background-color: rgba(80, 255, 80, 1);");// tema
    QIcon icon(":/Icons/smile.png");
    ui->startbut->setIcon(icon);

    QGridLayout *layout = new QGridLayout (ui->frame);// creacio del tauler de joc
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            Cell* s1=new Cell(i,j,0);
            Matriz_bombes[i][j]=s1;
            layout->addWidget(s1,i,j);
        }
    }

        timer = new QTimer(this);// crea el timer
        connect(timer, SIGNAL(timeout()), this, SLOT(temps()));
        connect(ui->startbut, SIGNAL(clicked()), this, SLOT(reset()));
        ui->time->display(seg);

        posar_mines();// posar les mines al camp
        ui->cont_mines->display(num_bombes);


            for (int i=0;i<9;i++){// connecta les mines i assigna el nombre de mines adjacents
                for(int j=0;j<9;j++){
            connect(Matriz_bombes[i][j], SIGNAL(wowClick(int,int,char)), this, SLOT(mouse_response(int,int,char)));
            posar_num_mines_adj();
                }
            }
}
void MainWindow::posar_num_mines_adj(){// posar a la cel·la corresponent el nombre de mines adjacents
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
    if (Matriz_bombes[i][j]->getCont()!=-1){
    int num=mines_adjacents(i,j);
    Matriz_bombes[i][j]->setCont(num);
    }
        }}
}

bool MainWindow::victoria(){// check si les condicions de victoria es compleixen si no retorna false
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
    if (Matriz_bombes[i][j]->getCont()==-1){
        if (Matriz_bombes[i][j]->getFlag()==false){
            return false;
        }
    }
    else{
        if (Matriz_bombes[i][j]->getClick()==false||Matriz_bombes[i][j]->getFlag()==true){
            return false;
        }
    }
}
    }
    return true;
}

void MainWindow::derrota(){// para el joc i para la interaccio amb el camp
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            Matriz_bombes[i][j]->blockSignals(true);
        }
    }
    timer->stop();
    estat_crnono=false;

}

void MainWindow::mostrar_bombes(int x,int y){// quan es perd s mostren les mines
    this->setStyleSheet("background-color: rgba(10, 210, 240, 1);");
    QIcon icon(":/Icons/freezing-face.png");
    ui->startbut->setIcon(icon);
    for (int i=0;i<9;i++){
        for(int j=0;j<9;j++){
    if (Matriz_bombes[i][j]->getCont()==-1){
        QIcon icon(":/Icons/bomb.png");
        Matriz_bombes[i][j]->setIcon(icon);
    }
    else if(Matriz_bombes[i][j]->getCont()!=-1&&Matriz_bombes[i][j]->getFlag()==true){// falses mines marcades
        QIcon icon(":/Icons/wrongflag.png");
        Matriz_bombes[i][j]->setIcon(icon);
    }
}
    }

    QIcon icon2(":/Icons/bomb_white.png");// la mina que s'ha clicat es un icono diferent a les altres
    Matriz_bombes[x][y]->setIcon(icon2);
}
void MainWindow::start_crono(){
   this->setStyleSheet("background-color: rgba(80, 255, 80, 1);");
    if (estat_crnono==false){
        timer->start(1000);
        estat_crnono=true;
    }
}
void MainWindow::Message(){// missatge de victoria
    QMessageBox msg;
    msg.setWindowTitle("VICTORIA");
    QPixmap exportSuccess(":/Icons/clinking-glasses");
    msg.setIconPixmap(exportSuccess);
    msg.setText("Enhorabona has erradicat el COVID-19");
    msg.addButton("Tancar", QMessageBox::YesRole);
    msg.exec();
}
