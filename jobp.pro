include (../geoseis.include)
TEMPLATE = app
QT += widgets
QT += testlib

DESTDIR =$(GEOSEIS)/bin 
TARGET = jobp
CONFIG += debug
#GEOSEIS = "d:\sea"


win32{
SEA_SRC = E:\openseaseis_v2.03
    LIBS += -L$(GEOSEIS)/lib\        
         -lseageolib -lseasystem -lproperty -lprojectBase -lseamod
    INCLUDEPATH += .\
	$(GEOSEIS)/include

    SOURCES += \
      $${SEA_SRC}\src\cs\segy\csSegyHdrMap.cc\
      $${SEA_SRC}\src\cs\system\csMethodRetriever.cc
    HEADERS += \
      $${SEA_SRC}\src\cs\segy\csSegyHdrMap.h\
      $${SEA_SRC}\src\cs\system\csMethodRetriever.h
}
!win32{
       LIBS += -L$(GEOSEIS)/lib \
	 -L$(GEOSEIS)/mod \
               -lgeolib -lcseis_system -lsegy -lsegd -lproperty -lprojectBase        
	        
       INCLUDEPATH += .\
		 ../projectbase \
		 $${PROPERTY_INCLUDE}\
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

