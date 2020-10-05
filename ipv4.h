/********************************************************
 * Alunos(as): Victor Hugo Brito da Silva Miranda
 *             Milena Bueno Carneiro
 * Professor: Wilmar Oliveira de Queiroz
 * Disciplina: Rede de Computadores II
 *
 * *****************************************************/

#ifndef IPV4_H
#define IPV4_H

#include <QMainWindow>

namespace Ui {
class Ipv4;
}

class Ipv4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ipv4(QWidget *parent = nullptr);
    ~Ipv4();

private slots:
    //Definição dos métodos da interface gráfica
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_lineEdit_5_returnPressed();

private:
    Ui::Ipv4 *ui;

    //Fuções(métodos)
    bool VerEntrada(QStringList&);
    void Calcular(QString&);
    QString OctetoBinario(QString&);


};

#endif // IPV4_H
