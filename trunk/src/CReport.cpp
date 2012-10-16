//------------------------------------------------------------------------------
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>
#include <QBuffer>
#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QtDebug>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include "CReport.h"
#include "CDocumentParser.h"
#include "CDocument.h"
#include "sch_libqt4report.cpp"
//------------------------------------------------------------------------------
namespace libqt4report {
	//------------------------------------------------------------------------------
	static CDocument * document;
	//------------------------------------------------------------------------------
	CReport::CReport(void) {
		log4cpp::PropertyConfigurator::configure("log4cpp.properties");
		document=0;
	}
	//------------------------------------------------------------------------------
	CReport::~CReport(void) {
		if(document != 0) {
			delete document;
		}
	}
	//------------------------------------------------------------------------------
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
	//------------------------------------------------------------------------------
	bool CReport::process(QFile *docFile) {
		QXmlSimpleReader xmlReader;
		QXmlInputSource *source = new QXmlInputSource(docFile);
		CDocumentParser *parser=new CDocumentParser();
		bool ret=false;
		
		xmlReader.setContentHandler(parser);
		qDebug() << "parse document";
		if(xmlReader.parse(source)) {
			qDebug() << "parse document ok";
			qDebug() << "getDocument";
			document=parser->getDocument();;
			
			qDebug() << "process document";
			if(document->process()) {
				qDebug() << "process document ok";
				ret=true;
			}else {
				qDebug() << "process document nok";
				lastError=document->getLastError();
			}
		}else {
			qDebug() << "parse document nok";
			lastError="Unable to parse the file : "+parser->errorString();
		}
		
		qDebug() << "cleanup";
		cleanup();
		qDebug() << "cleanup Ok";
		
		qDebug() << "delete objects";
		delete parser;
		delete source;
		qDebug() << "delete objects ok";
		
		return ret;
	}
	//------------------------------------------------------------------------------
	int CReport::getNbPage(void) {
		if(document != 0) {
			return document->getNbPage();
		}
		return 0;
	}
	//------------------------------------------------------------------------------
	QString CReport::toSvg(int pageIdx) {
		if(document != 0 && pageIdx >= 0 && pageIdx < document->getNbPage()) {
			return document->toSvg(pageIdx);
		}
		return "";
	}
	//------------------------------------------------------------------------------
	void CReport::cleanup(void) {
		if(document != 0) {
			document->cleanup();
		}
	}
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------