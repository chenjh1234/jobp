######################################################################
# Automatically generated by qmake (3.0) Fri Jan 23 08:58:38 2015
######################################################################

TEMPLATE = app
QT += widgets
QT += testlib

DESTDIR = Debug
TARGET = jobp
CONFIG += debug
#GEOSEIS = "d:\sea"
win32{
    LIBS += -L$(GEOSEIS)/lib\        
         -lseageolib -lseasystem -lproperty -lprojectBase -lseamod
    INCLUDEPATH += .\
	$(GEOSEIS)/include

    SOURCES += \
      D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\segy\csSegyHdrMap.cc\
      D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\system\csMethodRetriever.cc
    HEADERS += \
      D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\segy\csSegyHdrMap.h\
      D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\system\csMethodRetriever.h
}
!win32{
       LIBS += -L$(GEOSEIS)/lib \
               -lgeolib -lcseis_system -lsegy -lsegd -lproperty -lprojectBase         
       INCLUDEPATH += .\
	        $(GEOSEIS)/include
}

FORMS =  \
	flowdefine.ui
# Input
RESOURCES  += \
	jobp.qrc
SOURCES += jobp.cpp\
		csHelp.cc\
		mainwindow.cpp\
		listview.cpp\
		gsysinfo.cpp\
		flowapplication.cpp\
		flowdocument.cpp\
		flowtextwin.cpp\
		paramwin.cpp\
		modhelpwin.cpp\
		modlistwin.cpp\
		flowwin.cpp\
		flownode.cpp\
		runwin.cpp\
		flowdefine.cpp\
		tabledlg.cpp\
		modinfo.cpp

HEADERS += \
		csHelp.h\
		flowapplication.h\
		flowdocument.h\
		gsysinfo.h\
		mainwindow.h\
		listview.h\
		flowtextwin.h\
		paramwin.h\
		modhelpwin.h\
		modlistwin.h\
		flowwin.h\
		flownode.h\
		runwin.h\
		flowdefine.h\
		tabledlg.h\
		modinfo.h
