

/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/









#ifndef PISADORES_H
#define PISADORES_H

//#include <QObject>

#include <QTime>
#include <QTimer>
#include <QPushButton>
#include "bass.h"
#include "engine/Hth.h"
//#include "micelanea/CunaButton.h"


class Pisadores: public QObject
{

   Q_OBJECT              //cuidado!!!!! con esto habeces hace falta recompilar todo no vale con compilar

   private:
   QTimer *Timer;  // Timer Contador
   HSTREAM stream;
   Hth *w_Hth;
   bool IsHth;
   int HthTipo;
   int Dispositivo;
   QString Url;
   public:
   explicit Pisadores(QString url,QWidget *parent = 0);
   ~Pisadores();

   QString  Prefijo;
   void Configuracion(const QString Player);
   bool IsFinal(HSTREAM cual);  //determina el final de la cancion
   void Start();         //locuta el pisador
   QPushButton *boton;


   private slots:
    void Update();   //Procesa la hora
    void EmitInicio();   //Procesa la hora
    void EmitFinal();   //Procesa la hora

   //**********************************************************************
    signals:
    void Finish();  //emite al finalizar
    void Iniciar();  //emite al iniciar
    void FinishCuna(QPushButton*);  //emite al finalizar

};


#endif // PISADORES_H
