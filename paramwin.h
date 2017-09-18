
#ifndef PARAMWIN_H 
#define PARAMWIN_H 
 
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include "qttreepropertybrowser.h"
//#include "qtvariantpropertymanager.h"
#include "qtvariantproperty.h"
#include "qteditorfactory.h"

//#include "flowapplication.h"
#include "sysdefine.h"
#include "csParamDef.h"
#include "flownode.h"
// which module need a filedialog :
#define OPENFILE_MOD {(char*)"input",(char*)"input_ascii",\
                    (char*)"input_ascii",(char*)"input_segd",(char*)"input_segy",\
                    (char*)"output",(char*)"output_rsf",(char*)"output_segy",\
                     NULL}

#define OPENFILE_PARAM {(char*)"filename",(char*)"filename",\
                        (char*)"filename",(char*)"filename",(char*)"filename",\
                        (char*)"filename",(char*)"filename",(char*)"filename",\
                        NULL}

#define OPEN_FILE "openfile"
#define OPEN_CONSTANT "openconstant"
 

using namespace cseis_system;
using namespace std;

class paramWin :public QtTreePropertyBrowser//QWidget
{
    Q_OBJECT

public:
    paramWin(QWidget *p);
    ~paramWin();

    int createProperty(csParamDef *d);
    bool isOpenFile(char *mod,char *param);
    QString m_name;
    flowNode *m_node;
    QtEnumPropertyManager *m_mngE;
    

private:
    void init();
    QtVariantPropertyManager * m_mng;
    
    static QString dataSetPath;

    QtVariantEditorFactory * m_fct;
    
    QtEnumEditorFactory *m_fctE;
    QtPopupEditorFactory *m_fctPop;
 
protected:
    //gdata *data;
public slots:
   // void slotParam(QString s);
   // void slotShowParam(QString s);
    void slotOpenFile(QtVariantProperty *property, QtVariantPropertyManager *thisManager);
    void slotOpenConstant(QtVariantProperty *property, QtVariantPropertyManager *thisManager);
    void slotModify(QtProperty *  );
  
   
 
       


   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};



#endif
