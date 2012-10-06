//------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "CDocument.h"
//------------------------------------------------------------------------------
#define DPI				100
#define INCH			25.6
#define COEF			((double)DPI/INCH)
//------------------------------------------------------------------------------
namespace libqt4report {
	CDocument::CDocument(int pageWidth, int pageHeight) {
		fonts=new QHash<QString, QFont *>();
		
		pageHeader=docHeader=docBody=docFooter=pageFooter=0;
		
		this->pageWidth=pageWidth;
		this->pageHeight=pageHeight;
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
		
		createPages(&query);
		
		database.close();
		
		return true;
	}
	//------------------------------------------------------------------------------
	void CDocument::createPages(QSqlQuery *query) {
		int w=pageWidth*COEF, h=pageHeight*COEF;
		int y;
		int hPageHeader, hDocHeader, hDocBody, hDocFooter, hPageFooter;
		bool fini=(query->size() != 0);
		bool nouvellePage=true, finPage=false;
		QString svg;
		
		if(pageHeader != 0) {
			hPageHeader=pageHeader->getHeight();
		}
		
		if(docHeader != 0) {
			hDocHeader=docHeader->getHeight();
		}
		
		hDocBody=docBody->getHeight();
		
		if(docFooter != 0) {
			hDocFooter=docFooter->getHeight();
		}
		
		if(pageFooter != 0) {
			hPageFooter=pageFooter->getHeight();
		}
		
		while(!fini) {
			QSqlRecord record=query->record();
			processBand(&record);
			
			if(nouvellePage) {
				svg="<?xml version='1.0' encoding='utf-8'?>";
				svg+="<svg xmlns='http://www.w3.org/2000/svg' version='1.2' ";
				svg+="baseProfile='tiny' width='"+QString::number(w)+"' ";
				svg+="height='"+QString::number(h)+"'>";
				svg+="<rect x='0' y='0' width='"+QString::number(w)+"' height='"+QString::number(h)+"' fill='white' stroke='none' />";
			
				y=0;
				
				if(pageHeader != 0) {
					svg+=pageHeader->toSvg(&record, y);
				}
				
				if(query->first() && docHeader != 0) {
					svg+=docHeader->toSvg(&record, y);
				}
				
				nouvellePage=false;
			}
			
			if(finPage) {
				if(query->last()) {
					if(docFooter != 0) {
						svg+=docFooter->toSvg(&record, y);
					}
				}else {
					nouvellePage=true;
				}
				
				if(pageHeader != 0) {
					svg+=docFooter->toSvg(&record, y);
				}
				
				svg+="</svg>";
		
				qDebug() << svg;
		
				pages.append(svg);
			}
		}
		
	}
	//------------------------------------------------------------------------------
	void CDocument::processBand(QSqlRecord * record) {
	}
	//------------------------------------------------------------------------------
}