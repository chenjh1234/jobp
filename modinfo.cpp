#include "modinfo.h"
#include "comfun.h"
#include "csHelp.h"
#include "csVector.h"
#include <iostream>
#include <string>
#include <cstring>
#include "geolib_string_utils.h"
#include "csParamDef.h"
#include "csException.h"
#include "csMethodRetriever.h"
#include "csStandardHeaders.h"
#include "csHeaderInfo.h"
#include "csGeolibUtils.h"
#include "csSegyHdrMap.h"
#include "csHelp.h"
#include "filemng.h"
using namespace cseis_system;

modInfo::modInfo() 
{
        init();
  
}
modInfo::modInfo(string n) 
{
    init();
    setModule(n);
}

modInfo::~modInfo() 
{
    if (m_pDef != NULL)
    {
        delete m_pDef;
    }
}
void modInfo::init()
{
        m_pDef  = new csParamDef();
}
 
int modInfo::getInfoFromMap()
{
    string str,name;
    int i;
    //CONFIG config;
 
    map<string,flexVar>::iterator it;
   
    str = "";
    for (it = m_map.begin(); it != m_map.end();it++) 
    {
        if (it->first == "name") 
            name =  it->second.toString();
   
    }
    config = CONFIG(0);
     
    return 0;
} 
 
//==========================
int modInfo::getStatus()
{
    //fstream f;
    int i,uid;
    string str;
    struct stat sb;
    struct passwd *pwd;
    size_t found;
    dtime tm;
   

   // m_map[strlist[0]] = flexVar(name);
   

    return 0;
} 
int modInfo::getParam()
{
    csParamDef *pdef;
    pdef = m_pDef;

    csParamDescription const* const module = pdef->module();
    
 
    int nParams = pdef->numParameters();
    qDebug() <<"number of P ="<< nParams;

    csParamDescription const* valueDescriptor;
  
    for( int ip = 0; ip < nParams; ip++ ) 
    {
        qDebug() << "Pnumber = "<<ip ;
        qDebug() << "name = " << pdef-> param(ip)->name();
        qDebug() << "    type = " << pdef-> param(ip)->type();
        qDebug() << "    desc = " << pdef-> param(ip)->desc();
        qDebug() << "    descE = " << pdef-> param(ip)->descExtra();
        //pdef-> param(ip)->dump();

        int nValues = pdef->numValues(ip);

        for( int iv = 0; iv < nValues; iv++ ) 
        {
            qDebug() << "VVV= "<<iv ;
            valueDescriptor = pdef->value(ip,iv);
            if( strlen(valueDescriptor->name()) != 0 ) 
                printf("vname = %s  ", valueDescriptor->name());
            else 
                printf("vname = 0 " );

            qDebug() << "value type = " <<   valueDescriptor->type();
            qDebug() << "value desc = " <<   valueDescriptor->desc();
            qDebug() << "value descE = " <<   valueDescriptor->descExtra();
             //valueDescriptor->dump();
            
        }
      
    }    


    return 0;
}
int modInfo::setModule(string str)
{
    int i;
    name = str;
    
    i = setParamDef();
    if (i == 0)
    {
        return setHelp();
    }
    return -1;
}
int modInfo::setHelp()
{
    csHelp *h;
    h = new csHelp();
    m_strHelp = "";
/* 
    FILE *out;
    out = fopen( "modhelp.txt", "w" );
    h = new csHelp(out);
    h->moduleTextHelp(m_pDef->module()->name());
    fclose(out);
    QFile file("modhelp.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray ss;
    ss = file.readAll();
    m_strHelp = ss.data();
    file.close();
*/ 
    h->moduleHtmlHelp(*m_pDef,m_strHelp);
    return 0;
}
string modInfo::getHelp()
{
    return m_strHelp;
}
string modInfo::moduleName()
{
    return name;
}
csParamDef * modInfo::getPDef()
{
    return  m_pDef;
}
int modInfo::setParamDef()
{
    //std::string moduleName   = cseis_geolib::toUpperCase(moduleNameIn);
    //int numModules      = csMethodRetriever::getNumStandardModules();
    //std::string const* names = csMethodRetriever::getStandardModuleNames();
    csParamDef *pdef;
    pdef = m_pDef;

    MParamPtr funcPtr = NULL;
    //qDebug() << "start\n";
 
    try 
    {
        pdef->clear();
        funcPtr = csMethodRetriever::getParamMethod( name );
    }
    catch( cseis_geolib::csException& exc ) 
    {
        printf("%s", exc.getMessage());
        return -1;
    }
    //qDebug() << "func = " << funcPtr << "== after try \n";

    if( funcPtr != NULL ) 
    {
        funcPtr( &(*pdef ));
       // qDebug() <<"11111\n";     
        return 0;
    }
    return -2;

}
//========satrt mod mng=======================================================
void modMng::init()
{
   

 
}
//==========================
modMng::modMng()
{
    init();
}
//==========================
modMng::~modMng()
{
    //delete m_list;
}
 

//==========================
stringList modMng::modules() 
{
    return gsys.modules();
}
//============================
int  modMng::numModules() 
{
    return gsys.numModules();
}
 
//==========================
 
