//------------------------------------------------------------------------------
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "CDocument.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CDocument::CDocument(void) {
		fonts=new QHash<QString, QFont *>();
	}
	
	int CDocument::getNbPage(void) {
		return 1;
	}
	
	bool CDocument::render(int pageNo, CPage **page) {
		(*page)=new CPage(210, 297); //TODO xml
		
		return true;
	}
	
	void CDocument::setDatabaseInfos(QString driver, QString host, QString userName, QString password, QString dbName) {
		database=QSqlDatabase::addDatabase(driver);
		database.setHostName(host);
		database.setUserName(userName);
		database.setPassword(password);
		database.setDatabaseName(dbName);
	}
	
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
		
		database.close();
		
		return true;
	}
}
//------------------------------------------------------------------------------