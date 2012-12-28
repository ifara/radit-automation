
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/



#include <math.h>
#include <QTime>
#include <QDebug>
#include "StreamMath.h"

StreamMath::StreamMath()
{
}

StreamMath::StreamMath(HSTREAM stream)
{
    this->stream=stream;

}



void StreamMath::SetStream(HSTREAM stream){
 this->stream=stream;

}




double StreamMath::Duracion(){
    return(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)));
}

double StreamMath::Trascurridos(){
    return(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE)));
}



double StreamMath::Contador(){
    return(Duracion()-Trascurridos());
}


///////////////////////////////////////////////////////
QString StreamMath::SegundoToFormato(QString Formato){

   double Segundos=Duracion();

    long pos=Segundos*1000;
    long sec = pos/1000;
    long min = sec/60;
    long hour = min/60;
    long msec = pos;
    QTime *playTime = new QTime((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);

     return(playTime->toString(Formato));


}


QString StreamMath::SegundoToFormato(float Segundos,QString Formato){

   long pos=Segundos*1000;
   long sec = pos/1000;
   long min = sec/60;
   long hour = min/60;
   long msec = pos;
   QTime *playTime = new QTime((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);

    return(playTime->toString(Formato));

}


QString StreamMath::SegundoToFormato(){

    float Segundos= Duracion();
    long pos=Segundos*1000;
    long sec = pos/1000;
    long min = sec/60;
    long hour = min/60;
    long msec = pos;
    QTime *playTime = new QTime((int) hour%60, (int) min%60, (int) sec%60, (int) msec%1000);

     return(playTime->toString("hh:mm:ss:zzz"));


}


//****************Nivel de vumetro derecho ***********************

double StreamMath::VumetroDe(){
   //double level;
   int level;
    level=BASS_ChannelGetLevel(stream);
    return(ToDb(LOWORD(level)));

}
//****************Nivel vumetro izquierdo*********************

double StreamMath::VumetroIz(){
   //double level;
   int level;
    level=BASS_ChannelGetLevel(stream);
      return(ToDb(HIWORD(level)));

}

//************Retorna los decibelio **********************
double StreamMath::ToDb(double valor){

double db=20*log(valor/100); //log esta en <math.h>
  return(db);
}

///////////////////////////////////////////////////////////////
double StreamMath::FormatoToSegundos(QString Formato){

  QTime time = QTime::fromString(Formato, "HH:mm:ss"); // invalid

  double Minutos, Segundos;

  Minutos=time.hour()*60;
  Minutos= Minutos + time.minute();
  Segundos=Minutos *60 + time.second();

  //qDebug() <<time.hour() <<time.minute() <<time.second();
  return(Segundos);


}






