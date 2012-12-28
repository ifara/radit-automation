
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/




/** @brief Esta clase da soporte a un sistema aleatorio basado en carpetas.@a

     Controla que los ficheros
*    no se repitan. Típicamente recibe una carpeta y retorna un fichero aleatorio.
*
*
*
*/



#ifndef ALEATORIO_H
#define ALEATORIO_H

#include <QDirModel>
#include <QStatusBar>
#include <QVariant>
#include <QLabel>
#include <QFileSystemModel>






class Aleatorio
{

private:
QList<QString> results;
QList<int> Sacado;
QString Path;
int TotalFicheros;
int NumeroAleatorio(int range_starts, int range_ends);   // saca un numero aleatorio
bool Repetido(int numero);                              // comprueba sie sta repetido
void Todos();                                           // estan todos reproducidos
void Nuevo(int ultimo);                                 // marca el ultimo para que nos sea el primero
void CrearIndice(const QString url);

public:

   Aleatorio(const QString url,QLabel *w_Label);
  ~Aleatorio();



QString FicheroPath();


QString Cancion;   //para los titulos




};


#endif // ALEATORIO_H


