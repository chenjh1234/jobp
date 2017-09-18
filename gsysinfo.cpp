
#include "comfun.h"
#include "csHelp.h"
#include "csVector.h"
#include <iostream>
#include <string>
#include <cstring>
#include "geolib_string_utils.h"
#include "csParamDef.h"
#include "csException.h"
//#include "csMethodRetriever.h"
#include "csStandardHeaders.h"
#include "csHeaderInfo.h"
#include "csGeolibUtils.h"
#include "csSegyHdrMap.h"
#include "filemng.h"
#include "csMethodRetriever.h"

#include "gsysinfo.h"
using namespace cseis_system;

 
 
//========satrt mod mng=======================================================
void gsysInfo::init()
{
    setStdHeader();
    setModules();

 
}
//==========================
gsysInfo::gsysInfo()
{
    init();
}
//==========================
gsysInfo::~gsysInfo()
{
    //delete m_list;
}
string gsysInfo::getStdHeader()
{
    return m_stdHeader;
}
string gsysInfo::getStdHtmlHeader()
{
    return m_stdHtmlHeader;
}

//==========================
stringList gsysInfo::modules() 
{
    return m_moduleList;
}
//============================
int  gsysInfo::numModules() 
{
    return m_iModules;
}
 
//==========================
#ifdef WIN32
int gsysInfo::setModules() 
{
    int n,i;
    string *str,str1;
    n = csMethodRetriever::getNumStandardModules();
    str = (string *) csMethodRetriever::getStandardModuleNames();
    qDebug () << "modules = "<< n;
    for (i = 0; i< n; i++)
    { 
        qDebug() << "modules = " << str[i].c_str();
        str1 = cseis_geolib::toLowerCase( str[i] );
        str1 = str[i];
        m_moduleList.push_back(str1);
    }
    m_iModules = m_moduleList.size();
    return m_iModules;

}
#else
int gsysInfo::setModules() 
{
 
    string str,str1;
    char * pPath;
    string name;
    stringList strlist;

    pPath = getInstallDir();

    if(pPath == NULL)
    {
        MPR1("INSTALL_HOME is not defined\n");
        return -1;         
    }
 
    name = pPath ;
    name = name +  SLASH + "lib" ;
    strlist = findFiles((char *)name.c_str(), "libmod*.so");
    MPR2("size = %ld\n",strlist.size());
    int i,i1,i2;
    for (i = 0;i <strlist.size();i++) 
    {
        str = strlist[i];
        i1 = str.find("libmod")+ 7;
        i2 = str.find(".so");
      
        str1 = str.substr(i1,i2-i1); 
        // cout << i1 <<" " <<i2 << " " << str1.c_str() << endl;;
        m_moduleList.push_back(str1);
    }
 // add the ./ dir:
    name =".";
    name = name +  SLASH;
    strlist = findFiles((char *)name.c_str(), "libmod*.so");
    MPR2("size = %ld\n",strlist.size());
    //int i,i1,i2;
    for (i = 0;i <strlist.size();i++) 
    {
        str = strlist[i];
        i1 = str.find("libmod")+ 7;
        i2 = str.find(".so");
      
        str1 = str.substr(i1,i2-i1); 
        // cout << i1 <<" " <<i2 << " " << str1.c_str() << endl;;
        m_moduleList.push_back(str1);
    }


    m_iModules = m_moduleList.size();
    return m_iModules;
}
#endif
//==========================
void gsysInfo::setStdHeader() 
{
    char buffer[1024];
    m_stdHeader ="\0";
    cseis_geolib::csVector<cseis_geolib::csHeaderInfo const*> hdrList(40);
    cseis_geolib::csStandardHeaders::getAll( &hdrList );

    for( int ihdr = 0; ihdr < hdrList.size(); ihdr++ ) 
    {
        cseis_geolib::csHeaderInfo const* info = hdrList.at(ihdr);
        buffer[0] = '\0';
        sprintf(buffer,"Trace header #%3d: %-20s %-10s %s\n", ihdr+1, info->name.c_str(), cseis_geolib::csGeolibUtils::typeText(info->type), info->description.c_str() );
        m_stdHeader.append(buffer);
    }
    csHelp h;
    h.standardHeaderHtmlListing(m_stdHtmlHeader);
  
}
 
