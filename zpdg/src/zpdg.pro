TEMPLATE	= app
CONFIG		= qt warn_on debug
#CONFIG		= qt warn_on release
HEADERS		= zpdg.h
SOURCES		= main.cpp zpdg.cpp
INCLUDEPATH	+= $(QPEDIR)/include
DEPENDPATH	+= $(QPEDIR)/include
LIBS            += -lqpe
INTERFACES	= zpdgbase.ui
TARGET		= zpdg
