ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libqt4report.la

AM_CPPFLAGS = $(QT4_CFLAGS) $(LOG4CPP_CFLAGS) -DDATADIR='"$(datarootdir)"'

moc_FILES = 
		
INTERFACES =
		
ui_FILES = $(patsubst %.ui,ui_%.h, $(INTERFACES))

RESSOURCES = libqt4report.qrc
		
qrc_FILES = qrc_libqt4report.cpp

TRANSLATE =

lrelease_FILES = $(patsubst %.ts,%.qm, $(TRANSLATE))

libqt4report_la_SOURCES =	libqt4report.cpp libqt4report.h
						
nodist_libqt4report_la_SOURCES = $(moc_FILES) $(qrc_FILES)
			
libqt4report_la_LIBADD = $(QT4_LIBS) $(LOG4CPP_LIBS) 

libqt4report_ladir = $(datarootdir)/@PACKAGE@

libqt4report_la_DATA = $(lrelease_FILES) log4cpp.properties

dist_libqt4report_la_DATA = $(INTERFACES) $(TRANSLATE) $(RESSOURCES) log4cpp.properties

moc_%.cpp: %.h
	$(MOC) -o $@ $<
	
ui_%.h: %.ui
	$(UI) -o $@ $<
	
qrc_%.cpp: %.qrc
	$(RCC) -o $@ $<
	
%.qm: %.ts
	$(LRELEASE) $< -qm $@
	
$(libqt4report_la_OBJECTS): $(ui_FILES) $(moc_FILES) $(qrc_FILES) $(lrelease_FILES)

clean-qt-extra:
	rm -rf moc_*.cpp
	rm -rf ui_*.h
	rm -rf *.qm
	rm -rf qrc_*.cpp
	rm -rf *.o
	rm -f @PACKAGE@
	
clean-am: clean-qt-extra
