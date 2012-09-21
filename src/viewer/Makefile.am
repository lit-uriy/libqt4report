bin_PROGRAMS = viewer

AM_CPPFLAGS = $(QT4_CFLAGS) -I..  -DDATADIR='"$(datarootdir)"'

moc_FILES = moc_CMainFrm.cpp
		
INTERFACES = CMainFrm.ui
		
ui_FILES = $(patsubst %.ui,ui_%.h, $(INTERFACES))

RESSOURCES =
		
qrc_FILES = qrc_viewer.cpp

TRANSLATE =

lrelease_FILES = $(patsubst %.ts,%.qm, $(TRANSLATE))

viewer_SOURCES = 	viewer.cpp \
			CMainFrm.cpp CMainFrm.h
			
nodist_viewer_SOURCES = $(moc_FILES) $(qrc_FILES)
			
viewer_LDADD = $(QT4_LIBS) ../.libs/libqt4report.la

viewerdir = $(datarootdir)/@PACKAGE@

viewer_DATA = $(lrelease_FILES)

dist_viewer_DATA = $(INTERFACES) $(TRANSLATE)  $(RESSOURCES)

moc_%.cpp: %.h
	$(MOC) -o $@ $<
	
ui_%.h: %.ui
	$(UI) -o $@ $<
	
qrc_%.cpp: %.qrc
	$(RCC) -o $@ $<
	
%.qm: %.ts
	$(LRELEASE) $< -qm $@
	
$(viewer_OBJECTS): $(ui_FILES) $(moc_FILES) $(qrc_FILES) $(lrelease_FILES)

clean-qt-extra:
	rm -rf moc_*.cpp
	rm -rf ui_*.h
	rm -rf *.qm
	rm -rf qrc_*.cpp
	rm -rf *.o
	
clean-am: clean-qt-extra
