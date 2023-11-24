//*********************************************************************************************
//* Programme : Camera.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Théo ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But : Declarer la classe SerialCommunication et definir les fonctions qui permettent d'ouvrir,
//         de selection,de fermet et d'ecrire(sur) le port serie
//* Programmes associés :AUCUN
//*********************************************************************************************



#ifndef CAMERA_H
#define CAMERA_H   
#include <QSerialPortInfo>
#include <QObject>
#include <QSerialPort>
#include <QDebug>



// SerialCommunication.h

class SerialCommunication : public QObject
{
    Q_OBJECT

public:
    explicit SerialCommunication(QObject* parent = nullptr);
    ~SerialCommunication();
   
    bool openSerialPort(const QString& portName);
    bool configure();
    void closeSerialPort();
    bool writeData(const QByteArray& data);

    QStringList getAvailablePorts();

   
   
private:
    QSerialPort* serialPort;
};




#endif // CAMERA 
