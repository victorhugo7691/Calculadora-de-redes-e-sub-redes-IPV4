/********************************************************
 * Alunos(as): Victor Hugo Brito da Silva Miranda
 * Rede de Computadores II
 * *****************************************************/

#include "ipv4.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Ipv4 w;
    w.show();

    return a.exec();
}
