
#include "AcercaDe.h"



AcercaDe::AcercaDe(QDialog *parent )
    :QDialog(parent)
{
   setupUi(this);


   setModal(true);



#ifdef Q_OS_WIN32
 setWindowFlags( Qt::Tool);
#endif

 //evitamos que cambie el formulario
 QSize fixedSize(this->width(),this->height());
 setMinimumSize(fixedSize);
 setMaximumSize(fixedSize);
 setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


}
