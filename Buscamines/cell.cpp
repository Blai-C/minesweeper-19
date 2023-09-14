#include "cell.h"
#include <QPushButton>
#include "QMouseEvent"
#include <QFont>

Cell::Cell(int x, int y, int contCell, QPushButton *parent):QPushButton(parent),x(x),y(y),contCell(contCell){
    setStyleSheet("background-color: rgba(255, 255, 255, 0.7); border: none;"
                  "min-height:40; min-width:40;max-height:40; max-width:40;border-radius: 4px;");
}

// GETS

int Cell::getPosX()const{
    return x;
}
int Cell::getPosY()const{
    return y;
}
int Cell::getCont()const{
    return contCell;
}
bool Cell::getClick()const{
    return clicat;
}
bool Cell::getFlag()const{
    return flagged;
}
QString Cell::getIcon()const{
    return icon;
}

//SETS

void Cell::setPosX(int x){
    this->x=x;
}
void Cell::setPosY(int y){
    this->y=y;
}
void Cell::setCont(int contCell){
    this->contCell=contCell;
}
void Cell::setClick(bool clicat){
    this->clicat=clicat;
}
void Cell::setIcond(QString icon){
    this->icon=icon;
}

// accions QT

void Cell::Reset(){
    clicat=false;
    flagged=false;
    setIcond(nullptr);
    setStyleSheet("background-color: rgba(255, 255, 255, 0.7); border: none;"
                  "min-height:40; min-width:40;max-height:40; max-width:40;border-radius: 4px;");
    contCell=0;
    this->setText(NULL);

}
void Cell::showCont(){// mostrar cel·la
    if (contCell==-1){


    }
    else if (contCell==0){
        setStyleSheet("background-color: rgba(255, 255, 255, 0.2); border: none;"
                      "min-height:40; min-width:40;max-height:40; max-width:40;border-radius: 4px;");

    }
    else{
        QString aaa = QString::number(contCell);
        QFont sansFont("Arial", 16,QFont::Bold);
        this->setFont(sansFont);
        this->setText(aaa);
        setStyleSheet("background-color: rgba(255, 255, 255, 0.2); border: none;"
                      "min-height:40; min-width:40;max-height:40; max-width:40;border-radius: 4px;");
    }



}
// posar bandera
void Cell::setFlag(bool flag){
    flagged=flag;
}

// SIGNALS

void Cell::mousePressEvent(QMouseEvent *e)
{
    char but;

    //emits
    if(e->button()==Qt::RightButton){
        int x=this->getPosX();
        int y=this->getPosY();
        emit wowClick(x,y,but='R');}
    else if(e->button()==Qt::LeftButton){
        int x=this->getPosX();
        int y=this->getPosY();
        emit wowClick(x,y,but='L');}

    //this forwards the event to the QPushButton
    QPushButton::mousePressEvent(e);
}
