ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libqt4report.la

AM_CPPFLAGS = $(QT4_CFLAGS) $(LOG4CPP_CFLAGS) -DDATADIR='"$(datarootdir)"'

moc_FILES =

TRANSLATE =

lrelease_FILES = $(patsubst %.ts,%.qm, $(TRANSLATE))

libqt4report_la_SOURCES =	CReport.cpp CReport.h \
				CDocument.cpp CDocument.h \
				CDocumentParser.cpp CDocumentParser.h \
				CPrintableObject.h \
				CDocBand.cpp CDocBand.h \
				CItem.cpp CItem.h
						
nodist_libqt4report_la_SOURCES = $(moc_FILES)
			
libqt4report_la_LIBADD = $(QT4_LIBS) $(LOG4CPP_LIBS) 

libqt4report_ladir = $(datarootdir)/@PACKAGE@

libqt4report_la_DATA = $(lrelease_FILES) log4cpp.properties

dist_libqt4report_la_DATA = $(INTERFACES) $(TRANSLATE) $(RESSOURCES) log4cpp.properties

$(SCHEMA): schema/libqt4report.xsd
	echo -n 'static QByteArray schema("' > $@ 
	sed -e 's/\"/\\\"/g' -e 's/$$/\\/g' $< >> $@ 
	echo '");' >> $@

moc_%.cpp: %.h
	$(MOC) -o $@ $<
	
%.qm: %.ts
	$(LRELEASE) $< -qm $@

$(libqt4report_la_OBJECTS): $(moc_FILES) $(lrelease_FILES)
	
clean-qt-extra:
	rm -f *.o
	rm -f *.lo
	rm -f moc_*.cpp
	rm -f *.qm
	rm -f $(SCHEMA)
	
clean-am: clean-qt-extra
