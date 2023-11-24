//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 24/09/2023
//*
//* Programmeurs : BILHAUT Théo ,BRIAUX Simon,                                             Classe : BTSSN2
//*                NGANAMODEI Junior, PAZIAUD Hassan
//*--------------------------------------------------------------------------------------------
//* But : composition principale/point d'entrer du programme
//* Programmes associés :camera.h, QtCameraPilotage.h
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
     