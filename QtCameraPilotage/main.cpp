//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Th�o ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But : composition principale/point d'entrer du programme
//* Programmes associ�s :camera.h, QtCameraPilotage.h
//*********************************************************************************************
#include "QtCameraPilotage.h"
#include"camera.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCameraPilotage w;
    w.show();
    return a.exec();

}
     