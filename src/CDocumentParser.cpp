//--------------------------------------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlDatabase>
#include <log4cpp/Category.hh>
#include "CDocumentParser.h"
//--------------------------------------------------------------------------------------------------------------
namespace libqt4report {
	static log4cpp::Category& logger = log4cpp::Category::getInstance("CDocumentParser");
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::startDocument(void) {
		document=new CDocument();
		
		inFonts=inDatabase=inQuery=false;
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::endDocument(void) {
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) {
		int i;
		
		if(qName == "fonts") {
			qDebug()  << "Parse fonts element";
			inFonts=true;
			return true;
		}
		
		if(qName == "database") {
			qDebug()  << "Parse database element";
			inDatabase=true;
			return true;
		}
		
		if(qName == "query" && inDatabase) {
			qDebug()  << "Parse query element";
			inQuery=true;
			return true;
		}
		
		if(qName == "font" && inFonts) {
			QString id, family;
			int pointSize, weight;
			bool italic;
			QFont *f;
			
			for(i=0;i<atts.count();i++) {
				if(atts.localName(i) == "id") {
					id=atts.value(i);
				}else if(atts.localName(i) == "family") {
					family=atts.value(i);
				}else if(atts.localName(i) == "pointSize") {
					pointSize=atts.value(i).toInt();
				}else if(atts.localName(i) == "weight") {
					weight=atts.value(i).toInt();
				}else if(atts.localName(i) == "italic") {
					italic=(bool)atts.value(i).toInt();
				}
			}
			
			qDebug()  << "Add font" << id << "to collection";
			document->addFont(id, new QFont(family, pointSize, weight, italic));
			
			return true;
		}
		
		if(qName == "connection" && inDatabase) {
			QString driver, host, userName, password, dbName;
			
			for(i=0;i<atts.count();i++) {
				if(atts.localName(i) == "driver") {
					driver=atts.value(i);
				}else if(atts.localName(i) == "host") {
					host=atts.value(i);
				}else if(atts.localName(i) == "userName") {
					userName=atts.value(i);
				}else if(atts.localName(i) == "password") {
					password=atts.value(i);
				}else if(atts.localName(i) == "dbName") {
					dbName=atts.value(i);
				}
			}
			
			document->setDatabaseInfos(driver, host, userName, password, dbName);
			
			return true;
		}
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
		if(qName == "fonts") {
			qDebug()  << "End parse fonts element";
			inFonts=false;
			return true;
		}
		
		if(qName == "database") {
			qDebug()  << "End parse database element";
			inDatabase=false;
			return true;
		}
		
		if(qName == "query" && inDatabase) {
			qDebug()  << "End parse query element";
			inQuery=false;
			return true;
		}
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::characters(const QString& ch) {
		if(inQuery) {
			document->setQuery(ch);
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}
