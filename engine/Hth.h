
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************
 **
 **
 **
 **
 **
 ****************************************************************************/

#ifndef HTH_H
#define HTH_H







#include <QTime>
#include <QTimer>

#include "bass.h"


class Hth : public QObject
{

   Q_OBJECT              //cuidado!!!!! con esto habeces hace falta recompilar todo no vale con compilar

   private:
   QTimer *Timer;  // Timer Contador
   HSTREAM stream;

   bool IsHFinal;  // Ha reproducido la hora
   bool IsMFinal;   // H prefroducido minutos

   QString Path;

   bool IsHora;
   bool IsTemperatura;
   bool IsHumedad;
   void LeerClima();

   QString Temperatura;
   QString Humedad;
   int Dispositivo;

   public:
   explicit Hth(QObject *parent = 0);
   ~Hth();

   QString  Prefijo;
   void Configuracion(const QString Player);
   bool IsFinal(HSTREAM cual);             //determina el final de la cancion
   void StartHora();                       //locuta la hora
   void StartTemp();                      //locuta la temperatura
   void StartHumedad();                   //locuta la humedad

   private slots:
    void Update();                       //Procesa la hora




   //**********************************************************************
    signals:
    void Iniciar();              //señal inicia la locucion
    void Finish();               //señal finaliza la locucion



};



#endif // HTH_H
