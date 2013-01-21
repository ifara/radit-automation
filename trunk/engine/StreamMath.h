/**
 * StreamMath
 * -----------------------------------------
 *
 * - This class supports the mathematical system of the audio file.
 *
 * @author Victor Algaba
 */
#ifndef STREAMMATH_H
#define STREAMMATH_H

#include <QString>
#include "bass.h"

class StreamMath
{
    private:
        //HSTREAM stream;
        double ToDb(double valor);

    public:
        StreamMath(HSTREAM stream);
        StreamMath();
        ~StreamMath();
         HSTREAM stream;

        void SetStream(HSTREAM stream);
        double Duracion();//get duration in seconds
        double Trascurridos();//get time in progress
        double Contador();//Returns the duration in seconds elapsed minus

        /** Combierte segundos a formato "hh:mm:ss:zzz */
        QString SegundoToFormato();
        QString SegundoToFormato(QString Formato);
        QString SegundoToFormato(float Segundos,QString Formato="hh:mm:ss:zzz");

        double VumetroDe();//get level of DB of channel right
        double VumetroIz();//get level of DB of channel left

        double FormatoToSegundos(QString Formato);
};
#endif // STREAMMATH_H














