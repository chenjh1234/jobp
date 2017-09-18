#ifndef MODINFO_H
#define MODINFO_H

#include "sysdefine.h"
#include "baseinfo.h"
#include "dtime.h"
#include "flexvar.h"
#include "comfun.h"
#include "gsysinfo.h"
#include "csParamDef.h"
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
#include <QDebug>
using namespace cseis_system;
using namespace std;
/**
 * 
    modInfo mod;
    i = mod.setModule(modname);
    MPR2("setmod ret = %d\n",i);
 *  mod.getParam();
 *   */
class modInfo :public baseInfo
{
public:
   modInfo() ;
   modInfo(string moddname) ;
   ~modInfo();
  
   virtual int getStatus();
   //virtual int set(string path );
   virtual int getInfoFromMap();
   int setModule(string str);
   string moduleName();
   csParamDef* getPDef();
   int getParam();
   string getHelp();

 
private:
   int setParamDef();
   void init();
   csParamDef *m_pDef;
   int setHelp();
   string m_strHelp;
   
};
/**
 *  modMng mm;
 *   cout << "====start test modMng\n"
 *   stringList l;
 *   l = mm.modules();
 */

class modMng :public baseMng
{
public:

   modMng();
   ~modMng();
   char *getProjectHome();
  
  
   /**
     * module list in system
     * 
     * @return stringList 
    */
   stringList modules();
   /**
     * number of All system modules
     * 
     * @return int 
    */
   int numModules();


  
protected:
   
private:
    void init();
    gsysInfo gsys;
 
     
};
 
#endif

