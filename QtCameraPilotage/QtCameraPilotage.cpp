//*********************************************************************************************
//* Programme : QtCameraPilotage.cpp                                                      Date : 17/11/2023                                               
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Th�o ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But : Implementer les fonction de la classe QtCameraPilotage
//* Programmes associ�s :camera.h, QtCameraPilotage.h
//*********************************************************************************************
#pragma once
#include "QtCameraPilotage.h"
#include"camera.h"
#include <QThread>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QInputDialog>




QtCameraPilotage::QtCameraPilotage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    serialComm = new SerialCommunication(this);

    // Connecter les signaux/slots pour les boutons, sliders, etc.

    connect(ui.btnPowerOn, SIGNAL(clicked()), this, SLOT(camPowerOn()));
    connect(ui.btnPowerOff, SIGNAL(clicked()), this, SLOT(camPowerOff()));
    connect(ui.btnSelectPort, SIGNAL(clicked()), this, SLOT(selectSerialPort()));
    connect(ui.btncamPanRight, &QPushButton::clicked, this, &QtCameraPilotage::camPanRight);
    connect(ui.btncamPanLeft, &QPushButton::clicked, this, &QtCameraPilotage::camPanLeft);
    connect(ui.btncamTiltUp, &QPushButton::clicked, this, &QtCameraPilotage::camTiltUp);
    connect(ui.btncamTiltDown, &QPushButton::clicked, this, &QtCameraPilotage::camTiltDown);
    connect(ui.btncamScan, &QPushButton::clicked, this, &QtCameraPilotage::camScan);
    connect(ui.btnZoomTeleStandard, &QPushButton::clicked, this, &QtCameraPilotage::camZoomTeleStandard);
    connect(ui.btnZoomWideStandard, &QPushButton::clicked, this, &QtCameraPilotage::camZoomWideStandard);
    


}


QtCameraPilotage::~QtCameraPilotage()
{}

void QtCameraPilotage::sendCommand(const QString& command)
{
    QByteArray hexData = QByteArray::fromHex(command.toLatin1());

   
    serialComm->writeData(hexData);
}
// Alimenter la cam�ra
void QtCameraPilotage::camPowerOn() {
    sendCommand("81 01 04 00 02 FF ");

    qDebug() << "Bouton Power On appuy�.";
}

// �teindre la cam�ra
void QtCameraPilotage::camPowerOff() {
    sendCommand("81 01 04 00 03 FF");

    qDebug() << "Bouton Power Off appuy�.";
}
    
   
// Tourner la cam�ra � droite
void QtCameraPilotage::camPanRight(int panSpeed) {
    QString command= QString("81 01 06 01 16 10 02 03 FF").arg(panSpeed, 2);
    sendCommand(command.toUtf8());
    
    qDebug() << "Bouton Pan Right appuy�.";
}

// Tourner la cam�ra � gauche
void QtCameraPilotage::camPanLeft(int panSpeed) {
    QString command = QString("81 01 06 01 16 10 01 03 FF").arg(panSpeed, 2);
    sendCommand(command.toUtf8());

    qDebug() << "Bouton Pan Left appuy�.";
}

// Incliner la cam�ra vers le haut
void QtCameraPilotage::camTiltUp(int tiltSpeed) {
    QString command = QString("81 01 06 01 01 05 03 01 FF").arg(tiltSpeed, 2);
    sendCommand(command.toUtf8());
}

// Incliner la cam�ra vers le bas
void QtCameraPilotage::camTiltDown(int tiltSpeed) {
    QString command = QString("81 01 06 01 05 05 03 02 FF").arg(tiltSpeed, 2);
    sendCommand(command.toUtf8());
}

// Zoomer (standard)
void QtCameraPilotage::camZoomTeleStandard() {
    sendCommand("81 01 04 07 02 FF");
}
   
// D�zoomer (standard)
    void QtCameraPilotage::camZoomWideStandard() {
        sendCommand("81 01 04 07 03 FF");
    }

    //Zoomer (variable)
void QtCameraPilotage::camZoomTeleVariable(int speedParameter) {
    QString command = QString("81 01 04 07 22 FF").arg(speedParameter);
sendCommand(command.toUtf8());
}
    //D�zoomer(variable)
void QtCameraPilotage::camZoomWideVariable(int speedParameter) {
    QString command = QString("81 01 04 07 32 FF").arg(speedParameter);
    sendCommand(command.toUtf8());
}

// Arr�ter le mouvement de panoramique/inclinaison
void QtCameraPilotage::camPanTiltStop() {
    sendCommand("81 01 06 01 18 14 03 FF");
}
// Effectuer un balayage complet trois fois de suite avec un temps de pause de 3 secondes
void QtCameraPilotage::camScan() {
    const int numScans = 3;
    const int pauseTime = 3000; // 3 secondes
    const int panSpeed = 500;

    for (int i = 0; i < numScans; ++i) {
        // Balayage complet vers la droite
        camPanRight(panSpeed);
        QThread::msleep(3600);

        // Balayage complet vers la gauche
        camPanLeft(panSpeed);
        QThread::msleep(3600);
    }

    // Pause entre les balayages
    QThread::sleep(numScans * pauseTime / 1000);
}

// Fonction pour configurer le port s�rie
void QtCameraPilotage::configureSerialPort(SerialCommunication & serialPort) {

        // Configurer les param�tres du port s�rie (� adapter en fonction de vos besoins)

    serialPort.configure();

       
        QMessageBox::information(nullptr, "Information", "Port serie configure avec succ�s.");
}

QStringList QtCameraPilotage::getAvailablePorts()
{
    QStringList portList;

    // R�cup�rer la liste des ports s�rie disponibles
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    // Ajouter les noms des ports disponibles � la liste
    for (const QSerialPortInfo& port : ports) {
        portList.append(port.portName());
    }

    return portList;
}

void QtCameraPilotage::selectSerialPort()
{
   
    QStringList ports = getAvailablePorts();
  
    QInputDialog dialog;
    QString selectedPort;
    bool ok;

    selectedPort = dialog.getItem(nullptr, "S�eectionner le port serie", "Port serie :", ports, 0, false, &ok);

    // V�rifier si l'utilisateur a appuy� sur OK et a s�lectionn� un port
    if (ok && !selectedPort.isEmpty()) {

        if (serialComm->openSerialPort(selectedPort)) {
            
            configureSerialPort(*serialComm);
        }
        else {
            qDebug() << "Impossible d'ouvrir le port serie.";
        }
    }
    else {
       
        QMessageBox::warning(this, "Avertissement", "Aucun port serie selectionne.");
    }
}




