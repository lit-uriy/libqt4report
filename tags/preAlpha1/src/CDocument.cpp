//------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "CDocument.h"
#include "CFonts.h"
#include "CScript.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CDocument::CDocument(int pageWidth, int pageHeight) {
		pageHeader=docHeader=docBody=docFooter=pageFooter=0;
		
		this->pageWidth=pageWidth;
		this->pageHeight=pageHeight;
	}
	//------------------------------------------------------------------------------
	CDocument::~CDocument(void) {
		pages.clear();
	}
	//------------------------------------------------------------------------------
	int CDocument::getNbPage(void) {
		return pages.size();;
	}
	//------------------------------------------------------------------------------
	QString CDocument::toSvg(int pageIdx) {
		if(pageIdx >= 0 &&  pageIdx < pages.size()) {
			return pages.at(pageIdx);
		}
		return "";
	}
	//------------------------------------------------------------------------------
	void CDocument::setDatabaseInfos(QString driver, QString host, QString userName, QString password, QString dbName) {
		database=QSqlDatabase::addDatabase(driver);
		database.setHostName(host);
		database.setUserName(userName);
		database.setPassword(password);
		database.setDatabaseName(dbName);
	}
	//------------------------------------------------------------------------------
	bool CDocument::process(void) {
		if(!database.open()) {
			lastError=database.lastError().databaseText();
			
			return false;
		}
		
		QSqlQuery query(sqlQuery, database);
		if(!query.exec()) {
			lastError=query.lastError().databaseText();
			
			return false;
		}
		
		try {
			createPages(&query);
		}catch(QString *e) {
			lastError=*e;
			
			return false;
		}
		query.clear();
		database.close();
		
		return true;
	}
	//------------------------------------------------------------------------------
	void CDocument::cleanup(void) {
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
	}
	//------------------------------------------------------------------------------
	void CDocument::createPages(QSqlQuery *query) {
		int w=pageWidth*CPrintableObject::getCoef(), h=pageHeight*CPrintableObject::getCoef();
		int y;
		int hDocBody, hDocFooter=0, hPageFooter=0;
		int hFooter;
		bool fini;
		bool nouvellePage=true, finPage=false;
		QString svg;
		int idxRec, lastRec;
		
		hDocBody=docBody->getHeight();
		
		if(docFooter != 0) {
			hDocFooter=docFooter->getHeight();
		}
		
		if(pageFooter != 0) {
			hPageFooter=pageFooter->getHeight();
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
				svg="<?xml version='1.0' encoding='utf-8'?>";
				svg+="<svg xmlns='http://www.w3.org/2000/svg' version='1.2' ";
				svg+="baseProfile='tiny' width='"+QString::number(w)+"' ";
				svg+="height='"+QString::number(h)+"'>";
				svg+="<rect x='0' y='0' width='"+QString::number(w)+"' height='"+QString::number(h)+"' fill='white' stroke='none' />";
			
				y=0;
				
				if(pageHeader != 0) {
					svg+=pageHeader->toSvg(y);
				}
				
				if(idxRec == 0 && docHeader != 0) {
					svg+=docHeader->toSvg(y);
				}
				
				nouvellePage=false;
			}
			svg+=docBody->toSvg(y);
			
			hFooter=hPageFooter + (idxRec == lastRec-1 ? hDocFooter : 0);
			
			if(idxRec == lastRec || h - y - hFooter - hDocBody < 0) {
				finPage=true;
			}
			
			if(finPage) {
				if(idxRec == lastRec) {
					if(docFooter != 0) {
						svg+=docFooter->toSvg(y);
					}
					fini=true;
				}else {
					nouvellePage=true;
				}
				
				if(pageFooter != 0) {
					svg+=pageFooter->toSvg(y);
				}
				
				svg+="</svg>";
				
				pages.append(svg);
				
				//qDebug() << svg;
				
				finPage=false;
			}
			
			idxRec++;
		}
		
	}
	//------------------------------------------------------------------------------
}