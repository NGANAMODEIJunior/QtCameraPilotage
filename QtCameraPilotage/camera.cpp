//*********************************************************************************************
//* Programme : camera.cpp                                               Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Théo ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But : Implementer les fonction de la classe SerialCommunication
//* Programmes associés :camera.h
//*********************************************************************************************


#include <QSerialPortInfo>
#include "camera.h"

SerialCommunication::SerialCommunication(QObject* parent)
    : QObject(parent), serialPort(nullptr)
{
}

SerialCommunication::~SerialCommunication()
{
    closeSerialPort();
}

bool SerialCommunication::openSerialPort(const QString& portName)
{
    closeSerialPort();

    serialPort = new QSerialPort(this);
    serialPort->setPortName(portName);

    if (serialPort->open(QIODevice::ReadWrite))
    {
        return true;
    }
    else
    {
        qWarning() << "Echec de l'ouverture du port serie : " << serialPort->errorString();
        delete serialPort;
        serialPort = nullptr;
        return false;
    }
}

bool SerialCommunication::configure()
{
    if (!serialPort)
    {
        qWarning() << "Le port serie n'est pas initialise.";
        return false;
    }

    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    return true;
}

void SerialCommunication::closeSerialPort()
{
    if (serialPort && serialPort->isOpen())
    {
        serialPort->close();
        delete serialPort;
        serialPort = nullptr;
    }
}

bool SerialCommunication::writeData(const QByteArray& data)
{
    if (!serialPort || !serialPort->isOpen())
    {
        qWarning() << "Erreur : Le port serie n'est pas valide ou n'est pas ouvert.";
        return false;
    }

    qint64 bytesWritten = serialPort->write(data);

    if (bytesWritten == -1)
    {
        qWarning() << "Erreur lors de l'ecriture sur le port serie : " << serialPort->errorString();
        return false;
    }

    if (!serialPort->waitForBytesWritten(3000))
    {
        qWarning() << "Timeout lors de l'ecriture sur le port serie.";
        return false;
    }

    return true;
}
