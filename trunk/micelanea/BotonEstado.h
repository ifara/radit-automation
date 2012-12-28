/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.raditaudiopro.com)
 **
 ** *************************************************************************
 ** Cambia los colores tanto de los botones como de la lista de reproduccion
 **  Implementacion de la  clase
 **
 **
 **
 ****************************************************************************/






#ifndef BOTONESTADO_H
#define BOTONESTADO_H


#include <QPushButton>
#include <QTableWidget>


class BotonEstado

{

   private:

QPushButton *Boton;


   protected:

   public:
    BotonEstado();
    BotonEstado(QPushButton *w_Boton);
  virtual ~BotonEstado(){;}

    void SetActivo();
    void SetInactivo();
    void SetButton(QPushButton *w_Boton);

};


#endif // BOTONESTADO_H




















