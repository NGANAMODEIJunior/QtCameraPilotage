//*********************************************************************************************
//* Programme : QtCameraPilotage.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Th�o ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But :Definir la classe les fonctions, les slots necessairs pour l'application qui  g�re la camera
//* Programmes associ�s :camera.h, ui_QtCameraPilotage.h
//*********************************************************************************************


#pragma once
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include "ui_QtCameraPilotage.h"
#include "camera.h"

class QtCameraPilotage : public QMainWindow
{
    Q_OBJECT

public:
    QtCameraPilotage(QWidget* parent = nullptr);
    ~QtCameraPilotage();

private:
    Ui::QtCameraPilotageClass ui;
    SerialCommunication* serialComm;

    // Fonctions priv�es
    void sendCommand(const QString& command);
    void configureSerialPort(SerialCommunication& serialPort);
    QStringList getAvailablePorts();

    // Slots priv�s
private slots:

    void selectSerialPort();
    void camPowerOn();
    void camPowerOff();
    void camZoomTeleStandard();
    void camZoomWideStandard();
    void camZoomTeleVariable(int speedParameter);
    void camZoomWideVariable(int speedParameter);
    void camPanLeft(int panSpeed);
    void camPanRight(int panSpeed);
    void camTiltUp(int tiltSpeed);
    void camTiltDown(int tiltSpeed);
    void camPanTiltStop();
    void camScan();

};
