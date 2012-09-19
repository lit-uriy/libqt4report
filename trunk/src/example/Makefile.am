bin_PROGRAMS = example

AM_CPPFLAGS = $(QT4_CFLAGS) -I..

moc_FILES = 
		
INTERFACES =
		
ui_FILES = $(patsubst %.ui,ui_%.h, $(INTERFACES))

RESSOURCES =
		
qrc_FILES = 

example_SOURCES = example.cpp
			
nodist_example_SOURCES = $(moc_FILES) $(qrc_FILES)
			
example_LDADD = $(QT4_LIBS) ../.libs/libqt4report.la

exampledir = $(datarootdir)/@PACKAGE@

dist_example_DATA = $(INTERFACES) $(RESSOURCES)

moc_%.cpp: %.h
	$(MOC) -o $@ $<
	
ui_%.h: %.ui
	$(UI) -o $@ $<
	
qrc_%.cpp: %.qrc
	$(RCC) -o $@ $<
	
%.qm: %.ts
	$(LRELEASE) $< -qm $@
	
$(example_OBJECTS): $(ui_FILES) $(moc_FILES) $(qrc_FILES) $(lrelease_FILES)

clean-qt-extra:
	rm -rf moc_*.cpp
	rm -rf ui_*.h
	rm -rf *.qm
	rm -rf qrc_*.cpp
	rm -rf *.o
	
clean-am: clean-qt-extra
