/**
 * CurrentSound
 * -----------------------------------------
 *
 * - This class creates new file with information of the current song.
 * - file: CurrentSound.txt  folder: CurrentSound
 * - Out: title, artist, album,gender
 * - if don't have tag information , a out filename
 *
 * @author
 */
#ifndef FADER_H
#define FADER_H

#include <QThread>

#include "bass.h"

class Fader: public QThread
{

   Q_OBJECT

   public:
    Fader(QObject *parent = 0);
    Fader(HSTREAM Stream,int Fundir, QObject *parent = 0);

   void setStream(HSTREAM Stream);
   void setFundir(int Fundir);

   void run();


private:
    HSTREAM stream;
int Tiempo;

 signals:

};




#endif // FADER_H
