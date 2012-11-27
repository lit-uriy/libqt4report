//------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "CDocument.h"
#include "CFonts.h"
#include "CScript.h"
#include "CGroups.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CDocument::CDocument(QString pageWidth, QString pageHeight, QString unit, QString connectionName) : QList<CPage *>() {
		pageHeader=docHeader=docBody=docFooter=pageFooter=0;

		groupBands=new QHash<CGroup *, CDocBand *>();
		
		this->pageWidth=pageWidth;
		this->pageHeight=pageHeight;
		this->connectionName=connectionName;
		setUnit(unit);
	}
	//------------------------------------------------------------------------------
	CDocument::~CDocument(void) {
		int i;
		
		for(i=0;i<count();i++) {
			delete at(i);
		}
		
		clear();
		
		delete groupBands;
	}
	//------------------------------------------------------------------------------
	void CDocument::setDatabaseInfos(QString driver, QString host, QString userName, QString password, QString dbName) {
		if(connectionName.isEmpty()) {
			database=QSqlDatabase::addDatabase(driver);
			database.setHostName(host);
			database.setUserName(userName);
			database.setPassword(password);
			database.setDatabaseName(dbName);
		}else {
			database=QSqlDatabase::database(connectionName);
		}
	}
	//------------------------------------------------------------------------------
	bool CDocument::process(void) {
		if(connectionName.isEmpty()) {
			if(!database.open()) {
				lastSourceError=QObject::tr("Database error");
				lastError=database.lastError().databaseText();
			
				return false;
			}
		}
		
		QSqlQuery query(database);
		query.prepare(sqlQuery);
		
		QHashIterator<QString, QVariant> i(params);
		while (i.hasNext()) {
			i.next();
			query.bindValue(":"+i.key(), i.value());
		}
		
		if(!query.exec()) {
			lastSourceError=QObject::tr("Database error");
			lastError=query.lastError().databaseText();
			
			return false;
		}
		
		try {
			createPages(&query);
		}catch(QString *e) {
			lastSourceError=QObject::tr("Processing error");
			lastError=*e;
			
			return false;
		}
		
		query.clear();
		
		if(connectionName.isEmpty()) {
			database.close();
		}
		
		return true;
	}
	//------------------------------------------------------------------------------
	void CDocument::cleanup(void) {
		CGroups::getInstance()->cleanup();
		
		if(pageHeader != 0) {
			pageHeader->cleanup();
			delete pageHeader;
		}
		
		if(docHeader != 0) {
			docHeader->cleanup();
			delete docHeader;
		}
		
		if(docFooter != 0) {
			docFooter->cleanup();
			delete docFooter;
		}
		
		if(pageFooter != 0) {
			pageFooter->cleanup();
			delete pageFooter;
		}
		
		docBody->cleanup();
		delete docBody;
		
		CFonts::getInstance()->cleanup();
		CFields::getInstance()->cleanup();
		CScript::getInstance()->cleanup();
		
		QHashIterator<CGroup *, CDocBand *> i(*groupBands);
		while (i.hasNext()) {
			i.next();
			delete i.value();
		}
		groupBands->clear();
	}
	//------------------------------------------------------------------------------
	void CDocument::createPages(QSqlQuery *query) {
		int wPage=pageWidth.toInt()*coef;
		QString w=QString::number(wPage);
		int hPage=0;
		int y;
		int hDocBody, hDocFooter=0, hPageFooter=0;
		int hFooter;
		bool fini;
		bool nouvellePage=true, finPage=false;
		QString svg;
		int idxRec, lastRec;
		bool hSpecified=false;
		CPage *page;
		CPageManager *pageManager=new CPageManager(this);
				
		if(pageHeight != "100%") {
			hSpecified=true;
			hPage=pageHeight.toInt()*coef;
		}
		
		hDocBody=docBody->getHeight(coef);
		
		if(docFooter != 0) {
			hDocFooter=docFooter->getHeight(coef);
		}
		
		if(pageFooter != 0) {
			hPageFooter=pageFooter->getHeight(coef);
		}
		
		hFooter=hPageFooter;
		
		lastRec=query->size()-1;
		idxRec=0;
		fini=(lastRec == -1);
		
		while(!fini) {
			query->next();
			QSqlRecord record=query->record();
			
			processFields(&record);
			
			if(nouvellePage) {
				page=new CPage();
				
				svg="<?xml version='1.0' encoding='utf-8'?>";
				svg+="<svg xmlns='http://www.w3.org/2000/svg' version='1.2' ";
				svg+="baseProfile='tiny' width='"+w+"' ";
				svg+="height='${height}'>";
				svg+="<rect x='0' y='0' width='"+w+"' height='${height}' fill='white' stroke='none' />";
			
				y=0;
				
				if(pageHeader != 0) {
					svg+=pageHeader->toSvg(y, coef);
					pageHeader->prepareRender(page->getRendererObjects(), y, coef);
					y+=pageHeader->getHeight(coef);
				}
				
				if(idxRec == 0 && docHeader != 0) {
					svg+=docHeader->toSvg(y, coef);
					docHeader->prepareRender(page->getRendererObjects(), y, coef);
					y+=docHeader->getHeight(coef);
				}
				
				nouvellePage=false;
			}
			
			svg+=docBody->toSvg(y, coef);
			docBody->prepareRender(page->getRendererObjects(), y, coef);
			y+=docBody->getHeight(coef);
			
			hFooter=hPageFooter + (idxRec == lastRec-1 ? hDocFooter : 0);
			
			if(idxRec == lastRec || (hSpecified && hPage - y - hFooter - hDocBody < 0)) {
				finPage=true;
			}
			
			if(finPage) {
				if(idxRec == lastRec) {
					if(docFooter != 0) {
						svg+=docFooter->toSvg(y, coef);
						docFooter->prepareRender(page->getRendererObjects(), y, coef);
						y+=docFooter->getHeight(coef);
					}
					
					fini=true;
				}else {
					nouvellePage=true;
				}
				
				if(pageFooter != 0) {
					svg+=pageFooter->toSvg(y, coef);
					pageFooter->prepareRender(page->getRendererObjects(), y, coef);
					y+=pageFooter->getHeight(coef);
				}
				
				svg+="</svg>";
				svg.replace("${height}", QString::number(hSpecified ? hPage : y));
				
				page->setSvg(svg);
				
				append(page);
				
				finPage=false;
			}
			
			idxRec++;
		}
		pagesSize=QSize(wPage, hSpecified ? hPage : y);
		
		delete pageManager;
	}
	//------------------------------------------------------------------------------
}