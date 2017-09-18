#include "flowapplication.h"
flowApplication *theApp;

flowApplication::flowApplication( int & argc, char ** argv ):QApplication(argc,argv)
{
    init();
}
flowApplication::~flowApplication()
{

}
void  flowApplication::init()
{
    theApp = this;
}
