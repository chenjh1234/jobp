#ifndef GSYSINFO_H
#define GSYSINFO_H

using namespace std;
#include <sys/stat.h>
#include <sys/types.h>
//#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include "sysdefine.h"
#include "dtime.h"
#include "flexvar.h"
#include "comfun.h"
 
class gsysInfo 
{
public:
   gsysInfo() ;
   ~gsysInfo() ;
   char *getProjectHome();
    /**
     * standard system header
     * @return string 
     */
   string getStdHeader();
    /**
     * 
     * standard system header in html 
     *  
     * @return string 
     * 
     * @return string 
     */
   string getStdHtmlHeader();
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
    void setStdHeader();
    int setModules();

    string m_stdHeader,m_stdHtmlHeader; 
    stringList m_moduleList;
    int m_iModules;

  
 
   
};

 
 
#endif
