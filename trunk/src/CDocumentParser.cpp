//--------------------------------------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlDatabase>
#include <QMetaType>
#include <log4cpp/Category.hh>
#include "CDocumentParser.h"
#include "CFields.h"
#include "CFonts.h"
//--------------------------------------------------------------------------------------------------------------
namespace libqt4report {
	static log4cpp::Category& logger = log4cpp::Category::getInstance("CDocumentParser");
	//--------------------------------------------------------------------------------------------------------------
	CDocumentParser::CDocumentParser(void) {
		qRegisterMetaType<CItemTextFixedObject>("CItemTextFixedObject");
		qRegisterMetaType<CItemTextFieldObject>("CItemTextFieldObject");
		qRegisterMetaType<CDbFieldObject>("CDbFieldObject");
		qRegisterMetaType<CItemLineObject>("CItemLineObject");
		qRegisterMetaType<CItemRectObject>("CItemRectObject");
		qRegisterMetaType<CCalculatedFieldObject>("CCalculatedFieldObject");
		qRegisterMetaType<CTotalFieldObject>("CTotalFieldObject");
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::startDocument(void) {
		document=0;
		inFonts=inFields=inDatabase=inQuery=inBody=inField=false;
		curDocBand=edbtNone;
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::endDocument(void) {
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) {
		int i;
		
		if(qName == "document") {
			int pageWidth, pageHeight;
			
			for(i=0;i<atts.count();i++) {
				if(atts.localName(i) == "pageWidth") {
					pageWidth=atts.value(i).toInt();
				}else if(atts.localName(i) == "pageHeight") {
					pageHeight=atts.value(i).toInt();
				}
			}
			
			document=new CDocument(pageWidth, pageHeight);
			
			return true;
		}
		
		if(qName == "fonts") {
			qDebug()  << "Parse fonts element";
			inFonts=true;
			return true;
		}
		
		if(qName == "fields") {
			qDebug()  << "Parse fields element";
			inFields=true;
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
			int size;
			QString weight, style;
			CFont *font;
			
			for(i=0;i<atts.count();i++) {
				if(atts.localName(i) == "id") {
					id=atts.value(i);
				}else if(atts.localName(i) == "family") {
					family=atts.value(i);
				}else if(atts.localName(i) == "size") {
					size=atts.value(i).toInt();
				}else if(atts.localName(i) == "weight") {
					weight=atts.value(i);
				}else if(atts.localName(i) == "style") {
					style=atts.value(i);
				}
			}
			font=new CFont(family, size);
			if(!weight.isEmpty()) {
				font->setWeight(weight);
			}
			if(!style.isEmpty()) {
				font->setStyle(style);
			}
			
			qDebug()  << "Add font" << id << "to collection";
			CFonts::getInstance()->addFont(id, font);
			
			return true;
		}
		
		if(qName == "field" && inFields) {
			CField *field=parseField(atts);
			QString id=field->getAttribute("id");
			
			qDebug()  << "Add field" << id << "to collection";
			CFields::getInstance()->addField(id, field);
			
			curField=field;
			
			inField=true;
			
			return true;
		}
		
		if(qName == "expression" && curField != 0 && inField) {
			inFieldExpression=true;
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
		
		if(qName == "body") {
			qDebug()  << "Parse body element";
			inBody=true;
			return true;
		}
		
		if(qName == "pageHeader" && inBody) {
			qDebug()  << "Parse pageHeader element";
			document->createPageHeader();
			curDocBand=edbtPageHeader;
			return true;
		}
		
		if(qName == "docHeader" && inBody) {
			qDebug()  << "Parse docHeader element";
			document->createDocHeader();
			curDocBand=edbtDocHeader;
			return true;
		}
		
		if(qName == "docBody" && inBody) {
			qDebug()  << "Parse docBody element";
			document->createDocBody();
			curDocBand=edbtDocBody;
			return true;
		}
		
		if(qName == "docFooter" && inBody) {
			qDebug()  << "Parse docFooter element";
			document->createDocFooter();
			curDocBand=edbtDocFooter;
			return true;
		}
		
		if(qName == "pageFooter" && inBody) {
			qDebug()  << "Parse pageFooter element";
			document->createPageFooter();
			curDocBand=edbtPageFooter;
			return true;
		}
		
		if(qName == "item" && curDocBand != edbtNone) {
			qDebug()  << "Parse item element";
			CItem *item=parseItem(atts);
			if(item != 0) {
				switch(curDocBand) {
					case edbtPageHeader:
						document->getPageHeader()->insert(item->getAttribute("id"), item);
						break;
					case edbtDocHeader:
						document->getDocHeader()->insert(item->getAttribute("id"), item);
						break;
					case edbtDocBody:
						document->getDocBody()->insert(item->getAttribute("id"), item);
						break;
					case edbtDocFooter:
						document->getDocFooter()->insert(item->getAttribute("id"), item);
						break;
					case edbtPageFooter:
						document->getPageFooter()->insert(item->getAttribute("id"), item);
						break;
					default:
						break;
				}
			}
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
		
		if(qName == "fields") {
			qDebug()  << "End parse fields element";
			inFields=false;
			if(!CFields::getInstance()->processDepends()) {
				lastError=CFields::getInstance()->getDependsError();
				return false;
			}
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
		
		if(qName == "inBody") {
			qDebug()  << "End parse body element";
			inBody=false;
			return true;
		}
		
		if(inBody && (qName == "pageHeader" || qName == "docHeader" || qName == "docBody"|| qName == "docFooter" || qName == "pageFooter")) {
			qDebug()  << "End parse" <<  qName << "element";
			curDocBand=edbtNone;
			return true;
		}
		
		if(qName == "field" && inFields) {
			curField=0;
			inField=false;
			return true;
		}
		
		if(qName == "expression" && curField != 0 && inField) {
			inFieldExpression=false;
			return true;
		}
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool CDocumentParser::characters(const QString& ch) {
		if(inQuery) {
			document->setQuery(ch);
			return true;
		}
		
		if(inFieldExpression && curField != 0) {
			CCalculatedFieldObject *cfo=static_cast<CCalculatedFieldObject *>(curField);
			if(cfo != 0) {
				try {
					cfo->setExpression(ch);
				}catch(QString *e) {
					lastError=*e;
					return false;
				}
			}
			return true;
		}
		
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	CItem * CDocumentParser::parseItem(const QXmlAttributes& atts) {
		int i;
		QString className;
		CItem * item=0;
		
		for(i=0;i<atts.count();i++) {
			if(atts.localName(i) == "type") {
				className="CItem"+atts.value(i).left(1).toUpper()+atts.value(i).mid(1);
				
				int id=QMetaType::type(className.toUtf8().data());
				
				qDebug() << className << id;
				
				if(id != 0) {
					item=static_cast<CItem *>(QMetaType::construct(id));
				}
			}else {
				if(item != 0) {
					item->setAttribute(atts.localName(i), atts.value(i));
				}
			}
		}
		
		
		
		return item;
	}
	//--------------------------------------------------------------------------------------------------------------
	CField * CDocumentParser::parseField(const QXmlAttributes& atts) {
		int i;
		QString className;
		CField * field=0;
		
		for(i=0;i<atts.count();i++) {
			if(atts.localName(i) == "type") {
				className="C"+atts.value(i).left(1).toUpper()+atts.value(i).mid(1);
				
				int id=QMetaType::type(className.toUtf8().data());
				
				qDebug() << className << id;
				
				if(id != 0) {
					field=static_cast<CField *>(QMetaType::construct(id));
				}
			}else {
				if(field != 0) {
					field->setAttribute(atts.localName(i), atts.value(i));
				}
			}
		}
		
		
		
		return field;
	}
	//--------------------------------------------------------------------------------------------------------------
}