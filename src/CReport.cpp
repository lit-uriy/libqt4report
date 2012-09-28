//------------------------------------------------------------------------------
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>
#include <QBuffer>
#include <QPainter>
#include <QtDebug>
#include "CReport.h"
#include "sch_libqt4report.cpp"
//------------------------------------------------------------------------------
namespace libqt4report {
	bool CReport::validDocument(QFile *docFile) {
		QXmlSchema *xmlSchema=new QXmlSchema();
		bool ret=false;
		
		QByteArray data((const char *)schema_libqt4report_xsd, schema_libqt4report_xsd_size-1);
		QBuffer buffer(&data);
		buffer.open(QIODevice::ReadOnly);
		
		xmlSchema->load(&buffer);
		if(xmlSchema->isValid()) {
			QXmlSchemaValidator *validator=new QXmlSchemaValidator(*xmlSchema);
			
			if(validator->validate(docFile, QUrl::fromLocalFile(docFile->fileName()))) {
				ret=true;
			}
			
			delete validator;
		}
		
		delete xmlSchema;	
		
		return ret;
	}
	
	bool CReport::process(QFile *docFile, CDocument **document) {
		(*document)=new CDocument();
		
		return true;
	}
	
	QString CReport::getLastError(void) {
		return "";
	}
} //namespace
//------------------------------------------------------------------------------