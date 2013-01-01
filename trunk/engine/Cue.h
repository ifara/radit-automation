
/**
 * Cue
 * -----------------------------------------
 *
 * - Play file to Cue
 *
 *
 * @author Victor Algaba
 */







#ifndef CUE_H
#define CUE_H

#include "bass.h"

class Cue
{

  private:
    HSTREAM stream;

  public:
        Cue();
        Cue(HSTREAM Stream);
        virtual ~Cue(){;}

        void setDevice(int device);
        void setStream(HSTREAM Stream);

        void Play();
        void Stop();





  private slots:

  signals:




};





#endif // CUE_H
