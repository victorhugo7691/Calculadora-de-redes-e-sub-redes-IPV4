/********************************************************
 * Alunos(as): Victor Hugo Brito da Silva Miranda
 * Rede de Computadores II
 * *****************************************************/

#include "ipv4.h"
#include "ui_ipv4.h"
#include <iostream>
#include <bitset>
#include <math.h>
using namespace std;

Ipv4::Ipv4(QWidget *parent) :QMainWindow(parent), ui(new Ui::Ipv4){
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(press_compute()));
}

Ipv4::~Ipv4(){
    delete ui;
}

/*Este método está relacionado ao botão "Calcular", ao clicar, o método verifica se o IP é valido.
Sendo válido, ele transforma o número em 8 partes binárias.
Se não for válido, a função para*/
void Ipv4::on_pushButton_clicked(){

    QStringList IP_DecimalList = ui->lineEdit->text().split('.');
    if(!VerEntrada(IP_DecimalList)){
        ui->lineEdit->setText("Invalido");
        return;
    }
    int x= ui->lineEdit->text().toInt();
    QStringList IP_BinaryList;
    foreach (QString octet, IP_DecimalList)
        IP_BinaryList.append(QString::fromStdString(bitset<8>(octet.toInt()).to_string()));

    QString IPbinary = IP_BinaryList.join("");

    Calcular(IPbinary);
}

// O método "calcular" realiza o cálculo de todos os IP's,
void Ipv4::Calcular(QString& IPbinary){

    unsigned short int mascara = ui->lineEdit_5->text().toInt();

    //Tipo do endereço
    ui->lineEdit_8->setText(QString::number(pow(2, 32-mascara) - 2));
    QString netPortion = QStringRef(&IPbinary, 0, mascara).toString();

    //Cálculo para o IP da rede
    QString ipRede = netPortion + QString("0").repeated(32-mascara);
    ui->lineEdit_10->setText(ipRede);
    ipRede = OctetoBinario(ipRede);
    ui->lineEdit_2->setText(ipRede);

    //Cálculo para o primeiro Endereço
    QString primeiroEnd = netPortion + QString("0").repeated(32-mascara-1) + "1";
    ui->lineEdit_11->setText(primeiroEnd);
    primeiroEnd = OctetoBinario(primeiroEnd);
    ui->lineEdit_3->setText(primeiroEnd);

    //Cálculo do último endereço
    QString ultimoEnd= netPortion + QString("1").repeated(32-mascara-1) + "0";
    ui->lineEdit_12->setText(ultimoEnd);
    ultimoEnd = OctetoBinario(ultimoEnd);
    ui->lineEdit_4->setText(ultimoEnd);

    //Cálculo do endereço Bradcast
    QString broadcast= netPortion + QString("1").repeated(32-mascara);
    ui->lineEdit_13->setText(broadcast);
    broadcast = OctetoBinario(broadcast);
    ui->lineEdit_6->setText(broadcast);

    //Cálculo da máscara da rede
    QString mascaraRede = QString("1").repeated(mascara) + QString("0").repeated(32-mascara);
    ui->lineEdit_14->setText(mascaraRede);
    mascaraRede = OctetoBinario(mascaraRede);
    ui->lineEdit_7->setText(mascaraRede);
}

//A função OctetoBinatio recebe o Ip em decimal e converte para em binário de 8 partes
QString Ipv4::OctetoBinario(QString& IPbinary){
    QStringList netAddressList;
    for (int i = 0; i < 32; i+=8){
        QString intOctet = QString::number(QStringRef(&IPbinary, i, 8).toString().toInt(nullptr, 2));
        netAddressList.append(intOctet);
    }

    return netAddressList.join(".");
}

/*O método VerEntrada, verifica se a entrada é válida.
 * Aqui, se a mascara for menor que zero, ou maior que 28 ele retorna que é inválida.
 * Se o ip não seguir o padrão xxxx.xxxx.xxxx.xxxx considerando 4 partes, ele retorna que é inválido
 * E se em cada uma das divisões, os octetos não corresponderem ao tamanho >=0 até 255, ele retorna que é invalido*/
bool Ipv4::VerEntrada(QStringList& IP_DecimalList){
    int mask = ui->lineEdit_5->text().toInt();
    if(mask < 0 || mask > 28){
        qDebug("Mascara Invalida");
        return false;
    }

    if(IP_DecimalList.length() != 4)
        return false;

    foreach (QString octet_str, IP_DecimalList){
        int octet = octet_str.toInt();
        if(octet < 0 || octet > 255){
            qDebug("IP invalido");
            return false;
        }
    }

    return true;
}

//Função para atividades da interface gráfica
void Ipv4::on_lineEdit_returnPressed(){
    ui->lineEdit_5->setFocus();
    ui->lineEdit_5->selectAll();
}

//Função para atividades da interface gráfica
void Ipv4::on_lineEdit_5_returnPressed(){
    ui->pushButton->click();
}

