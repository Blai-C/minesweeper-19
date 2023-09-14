#ifndef CELL_H
#define CELL_H
#include <QPushButton>



class Cell : public QPushButton{
    Q_OBJECT
public:

    Cell(int x, int y, int contCell, QPushButton *parent = nullptr);

public slots:

    // GETS

    int getPosX()const;
    int getPosY()const;
    int getCont()const;
    bool getClick()const;
    bool getFlag()const;
    QString getIcon()const;

    //SETS

    void setPosX(int x);
    void setPosY(int y);
    void setCont(int contCell);
    void setClick(bool clicat);
    void setIcond(QString icon);
    void setFlag(bool flag);

    // accions QT

    void Reset();
    void showCont();

    // mousepress
    void mousePressEvent(QMouseEvent *e);


signals:
    void wowClick(int a, int b,char c);//envia la senyal quan es clica una cell


private:
    int x;
    int y;
    int contCell;// Bomba=-1 Res=0 Nums==nums (1,2,3,4)

    bool clicat=false;
    bool flagged=false;
    QString icon;

    Cell *m_cell;



};


#endif // CELL_H
