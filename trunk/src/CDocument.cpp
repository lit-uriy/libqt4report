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
		int pageIdx=0;
		int heightFooter=0;
		bool lastPage=false;

		QString svg="<?xml version='1.0' encoding='utf-8'?>\
		<svg xmlns='http://www.w3.org/2000/svg' version='1.2' \
		baseProfile='tiny' width='"+QString::number(w)+"' \
		height='"+QString::number(h)+"'>";
		
		svg+="<rect x='0' y='0' width='"+QString::number(w)+"' height='"+QString::number(h)+"' fill='white' stroke='none' />";
		
		if(pageFooter != 0) {
			heightFooter=pageFooter->getHeight();
		}
		
		y=0;
		while(query->next()) {
			QSqlRecord record=query->record();
			
			if(y == 0) {
				if(pageHeader != 0) {
					svg+=pageHeader->toSvg(&record, y);
					y+=pageHeader->getHeight();
				}
				
				if(pageIdx == 0 && docHeader != 0) {
					svg+=docHeader->toSvg(&record, y);
					y+=docHeader->getHeight();
				}
			}
			
			svg+=docBody->toSvg(&record, y);
			y+=docBody->getHeight();
			
			if(lastPage && docFooter != 0) {
				svg+=docFooter->toSvg(&record, y);
				y+=docFooter->getHeight();
			}
			
			if(pageFooter != 0) {
				svg+=pageFooter->toSvg(&record, y);
				y+=pageFooter->getHeight();
			}
		}
		
		svg+="</svg>";
		
		qDebug() << svg;
		
		pages.append(svg);
	}
	//------------------------------------------------------------------------------
}