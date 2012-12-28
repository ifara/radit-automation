/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/





#ifndef PLAYERSETTING_H
#define PLAYERSETTING_H

#include "ui_FrmSetting.h"




class PlayerSetting : public QDialog, private Ui::FrmSetting
 {
     Q_OBJECT

 private:
    void AddDispositivo();
    void Establecer();
    QString w_Modulo;

 public:
     explicit PlayerSetting(QString Modulo,QDialog *parent = 0);
     virtual ~PlayerSetting(){;}
     void SetPos(QRect scr);


 private slots:
     void ClickSalir();


};



#endif // PLAYERSETTING_H
