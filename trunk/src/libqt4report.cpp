//------------------------------------------------------------------------------
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>
#include <QtDebug>
#include "libqt4report.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	bool validDocument(QFile *docFile) {
		QXmlSchema *xmlSchema=new QXmlSchema();
		QFile *xsdFile=new QFile(":/libqt4report/schema/libqt4report.xsd");
		xsdFile->open(QIODevice::ReadOnly);
		bool ret=false;
		
		xmlSchema->load(xsdFile, QUrl::fromLocalFile(xsdFile->fileName()));
		if(xmlSchema->isValid()) {
			QXmlSchemaValidator *validator=new QXmlSchemaValidator(*xmlSchema);
			
			if(validator->validate(docFile, QUrl::fromLocalFile(docFile->fileName()))) {
				ret=true;
			}
			
			delete validator;
		}
		
		delete xsdFile;
		delete xmlSchema;	
		
		return ret;
	}
} //namespace
//------------------------------------------------------------------------------