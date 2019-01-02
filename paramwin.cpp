#include "paramwin.h"
#include "flowapplication.h"
#include "csParamDef.h"
#include "flownode.h"
#include <QMessageBox>
#include <QtGlobal>
using namespace cseis_system;
QString paramWin::dataSetPath = "";

paramWin::paramWin(QWidget *p):QtTreePropertyBrowser(p)//QWidget(p)
{
    init();
}
//=======================
paramWin::~paramWin()
{

}

//=======================
void paramWin::init()
{  
 

    m_mngE = new QtEnumPropertyManager();
    m_mng = new QtVariantPropertyManager();
    
    m_fct = new QtVariantEditorFactory();
    m_fctE = new QtEnumEditorFactory();
    m_fctPop = new QtPopupEditorFactory();

    setFactoryForManager(m_mng, m_fct); 
    setFactoryForManager(m_mngE, m_fctE);

    m_name = "";
    m_node =NULL;


/*

    QtProperty *i1 =m_mng->addProperty(QVariant::Int,"you");
     QtProperty *i2 =m_mng->addProperty(QVariant::Bool,"BOOL");
    //setFactoryForManager(m_mng, m_fct);
    addProperty(i1);
    addProperty(i2);
*/
     

}

int paramWin::createProperty(csParamDef *pDef)
{
    csParamDef *pdef;
    QString name,vname,pdesc,vdesc,disName,modname,str;
    QStringList strList;
    QVariant vv;
    int nOptions;
    bool pathConnect,constantConnect;
    pathConnect = true;
    constantConnect = true;

    pdef = pDef;
    QtProperty *pt,*pt0,*pt1;
    pt = pt0 =NULL;

 

    csParamDescription const* const module = pdef->module();
    if (module == NULL)
    {
        // no this module:
        name = windowTitle();
        str = QString(" No this module: ") + name;
        QMessageBox::warning(this,"error",str);
        return -1;
    }

    modname = module->name();
    clear();
    //m_mng->clear();

    int nParams = pdef->numParameters();
    qDebug() <<"number of P ="<< nParams;

    csParamDescription const* valueDescriptor;
    csParamDescription const* optionDescriptor;
  /*
    /// Parameter type:
  static const int NUM_VALUES_FIXED    = 11;
  static const int NUM_VALUES_VARIABLE = 12;
  /// Value type:
  static const int VALTYPE_OPTION = 21;
  static const int VALTYPE_NUMBER = 22;
  static const int VALTYPE_STRING = 23;
  static const int VALTYPE_HEADER_NUMBER = 24;   
    */ 
   
    for( int ip = 0; ip < nParams; ip++ ) 
    {
#if 0
        qDebug() << "Pnumber = "<<ip ;
        qDebug() << "name = " << pdef-> param(ip)->name();
        qDebug() << "    type = " << pdef-> param(ip)->type();
        qDebug() << "    desc = " << pdef-> param(ip)->desc();
        qDebug() << "    descE = " << pdef-> param(ip)->descExtra();
        
        pdef-> param(ip)->dump();
#endif
        name = pdef-> param(ip)->name();

       // pt = m_mng->addProperty(QVariant::String,name);
        pdesc = pdef-> param(ip)->desc();
        //pt->setToolTip(qs);

        int nValues = pdef->numValues(ip);
        //strList = "";

        for( int iv = 0; iv < nValues; iv++ ) 
        {
            //qDebug() << "VVV= "<<iv ;
            vname = "";
            valueDescriptor = pdef->value(ip,iv);
            if( strlen(valueDescriptor->name()) != 0 ) 
            {
                //qDebug("vname = %s  ", valueDescriptor->name());
                vname = valueDescriptor->name();
            }
            else 
            {
               // qDebug("no vname = 0 " );
               // vname = " ";
            }
             
#if 1
            qDebug() << "value name = " <<   valueDescriptor->name();
            qDebug() << "value type = " <<   valueDescriptor->type();
            qDebug() << "value desc = " <<   valueDescriptor->desc();
            qDebug() << "value descE = " <<   valueDescriptor->descExtra();

           // pt = m_mng->addProperty(QVariant::String, name); 
#endif
            if (valueDescriptor->desc()) vdesc = valueDescriptor->desc() ; 
            else vdesc =""; 
            // first value: disname = parameter name,else ""
            if (iv == 0) disName =name;
                else disName ="";
            //
            //qDebug() << "0vv vname ="<<vv<<vname;
            vv.clear();
            //qDebug() << "1vv vname ="<<vv<<vname;
            if (vname.length() >0)  //default name
                vv = vname; 
            else
                vv = "";
           // vv = "" ;//leave the default to "", 
                     //when read flow file ,it will exactly mathch the text flow file.
            //qDebug() << "vv vname ="<<vv<<vname;

            int idx = 0;
            int pathId ;
            switch (valueDescriptor->type()) 
            {
            case VALTYPE_OPTION:
            case VALTYPE_HEADER_NUMBER:   
                 nOptions = pdef->numOptions(ip,iv);
                 strList.clear();

                 for( int io = 0; io < nOptions; io++ )
                 {
                     optionDescriptor = pdef->option(ip,iv,io);
                     Q_ASSERT(optionDescriptor->name() !=NULL);
                     strList.append(optionDescriptor->name());
                     if (vname == optionDescriptor->name()) idx = io;
                 }
                 vv=strList;
                 qDebug() << "head,option,   name =" << name << "m_mng = " << m_mng << vv;

                 pt0 = m_mngE->addProperty( disName); 
                 m_mngE->setEnumNames(pt0, strList);
                  
                 Q_CHECK_PTR(pt0);
                 
                 //m_mngE->setValue(pt0,0);
                 m_mngE->setValue(pt0,idx);
                 
                 break;
            case VALTYPE_NUMBER:
                  
                 //pt0 = m_mng->addProperty(QVariant::Double, disName); 
                 //pt0 = m_mng->addProperty(QVariant::String, disName); 
                 pathId = m_mng->pathTypeId();
                 pt0 = m_mng->addProperty(pathId, disName);
                 if (constantConnect) 
                 {
                 
                     connect(m_mng, SIGNAL(openPathTriggered(QtVariantProperty * , QtVariantPropertyManager * )), 
                         this, SLOT(slotOpenConstant(QtVariantProperty* , QtVariantPropertyManager * )));
                     constantConnect = false;

                 }
                 if (vv.isValid())  
                 {
                     qDebug() << "number = " <<name << " "<< vname << vv;
                     //m_mng->setValue(pt0, vv.toDouble()); 
                     m_mng->setValue(pt0, vv.toString());
                     pt0->setStatusTip(OPEN_CONSTANT);
                      
                 }
                 else
                 {
                     // set default here;
                 }
                  
                 break;
            case VALTYPE_STRING:
                 //pt0 = m_mng->addProperty(QVariant::String, disName); 
                 pathId = m_mng->pathTypeId();
                 pt0 = m_mng->addProperty(pathId, disName);
                 if (isOpenFile(modname.toUtf8().data(),name.toUtf8().data()))
                 {
                     if (pathConnect) //ensure connect   one time
                     {
                         connect(m_mng, SIGNAL(openPathTriggered(QtVariantProperty * , QtVariantPropertyManager * )), 
                                 this, SLOT(slotOpenFile(QtVariantProperty* , QtVariantPropertyManager * )));
                         pathConnect = false;
                     }
                     str = OPEN_FILE+modname;
                     //pt0->setStatusTip(OPEN_FILE);
                     pt0->setStatusTip(str.toUtf8().data());
                 }
                 else
                 {
                     if (constantConnect) //ensure connect   one time
                     {
                         connect(m_mng, SIGNAL(openPathTriggered(QtVariantProperty * , QtVariantPropertyManager * )), 
                                 this, SLOT(slotOpenConstant(QtVariantProperty* , QtVariantPropertyManager * )));
                         constantConnect = false;
                     }
                     pt0->setStatusTip(OPEN_CONSTANT);
                 }

                 //vv ="";
                 if (vv.isValid())
                     m_mng->setValue(pt0,vv.toString());
                 break;
            }            
  
            pt0->setToolTip( vdesc);
            //pt0->setPropertyName ( vdesc);
            //setWhatsThis();
   
            //pt0->setModified(true);
            pt0->setEnabled(true);
            qDebug() <<" set modify = "<< name;
             
            if (iv ==0 ) pt = pt0; 
            if (iv > 0) 
            {   
                pt->addSubProperty(pt0); 
            }
             
        }//end of value;
        addProperty(pt);    
    }  // end of param  

    connect(m_mng,SIGNAL(propertyChanged( QtProperty *)),
                         this,SLOT(slotModify(QtProperty *)));
    connect(m_mngE,SIGNAL(propertyChanged( QtProperty *)),
                         this,SLOT(slotModify(QtProperty *)));
  
    return 0;
}
void paramWin::slotOpenFile(QtVariantProperty *property, QtVariantPropertyManager *thisManager)
{
    
   // if (property ->statusTip() != OPEN_FILE)  return;
    QString fileName,str,path,modi,outid,opflag;
    bool bsave;
    bsave = false;
    outid = "output";
    opflag = OPEN_FILE;
    str = property ->statusTip();
    if (str.left(8) != QString(OPEN_FILE)) return;
    modi = str.mid(8,6).toLower();
    qDebug() << "modi = "<<modi;
    if (modi== outid)  
        bsave = true;
    
    int i;
    path = theApp->m_doc->m_dataHome;
    if (path.isEmpty()) 
    {
        path = dataSetPath;
    }
    if (bsave) 
    {
        fileName = QFileDialog::getSaveFileName(this, 
             tr("Save File"), path, tr("data Files (*.*)"));
    }
    else
    {
 
        fileName = QFileDialog::getOpenFileName(this, 
             tr("Open File"), path, tr("data Files (*.*)"));
    }
    QFileInfo fi(fileName);
    i = fileName.lastIndexOf(SLASH);
    str = fileName.left(i+1);
    dataSetPath = str;// remember the last set;
    //qDebug() << "flowPath = " << flowPath <<str <<i;
    //setText(fileName);

    property->setValue(fileName); 
}
void paramWin::slotOpenConstant(QtVariantProperty *property, QtVariantPropertyManager *thisManager)
{
    if (property ->statusTip() != OPEN_CONSTANT)  return;
    qDebug() << "slotOpenConstant = " << property->propertyName()  ;//name;

    int i;
    QString str;
    str = "";
    i = theApp->m_win->defineView->exec();
    //qDebug() << "return = " << i;
    if (i !=0)
    {
        str = theApp->m_win->defineView->getSelect();
        if(str != "")
        {
            str = "&" + str + "&";
            property->setValue(str);
        }
        //qDebug() << "define = " <<str;
    }
     
}
void paramWin::slotModify(QtProperty *pro  )
{
    //qDebug() << "modifyed enter " ;
    if(theApp->m_doc->m_loadFile) return;

    theApp->m_win->setWindowModified(true);//modify
    qDebug() << "modifyed = " << pro->propertyName() ;
}
bool paramWin::isOpenFile(char *mod,char *param)
{

    int i;
    char *mods[] =   OPENFILE_MOD;
    char *params[] =   OPENFILE_PARAM;
    QString strMod,strParam,str1,str2;
    strMod = mod;
    strParam = param;
    // qDebug() << "mod = " << mod << param;
    qDebug() << "is OpenFile mod = " << strMod.toLower()<< strParam.toLower();
    i = 0;
    while (mods[i] !=NULL) 
    {
      
       str1 = mods[i];
       str2 = params[i];
       qDebug() <<  "mod param = "<<str1<<str2;
       if (str1.toLower() == strMod.toLower() && str2.toLower() == strParam.toLower())  
       {
           qDebug() << "openfile = " << mod << ":"<< param;
           return true;
       }
       i++;
    }
    return false;

}
