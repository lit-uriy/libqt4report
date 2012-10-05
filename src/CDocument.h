//------------------------------------------------------------------------------
#ifndef __CDOCUMENT_H__
#define __CDOCUMENT_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QFont>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include "CDocBand.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CDocument {
		public:
			CDocument(int pageWidth, int pageHeight);
			int getNbPage(void);
			QString toSvg(int pageIdx);
			QString getLastError(void) { return lastError; }
			void addFont(QString id, QFont *font) { fonts->insert(id, font); }
			QFont *getFont(QString id) { return fonts->value(id); }
			void setDatabaseInfos(QString driver, QString host, QString userName, QString password, QString dbName);
			void setQuery(QString sqlQuery) { this->sqlQuery=sqlQuery.trimmed(); }
			bool process(void);
			void createPageHeader(void) { pageHeader=new CDocBand(); }
			void createDocHeader(void) { docHeader=new CDocBand(); }
			void createDocBody(void) { docBody=new CDocBand(); }
			void createDocFooter(void) { docFooter=new CDocBand(); }
			void createPageFooter(void) { pageFooter=new CDocBand(); }
			CDocBand * getPageHeader(void) { return pageHeader; }
			CDocBand * getDocHeader(void) { return docHeader; }
			CDocBand * getDocBody(void) { return docBody; }
			CDocBand * getDocFooter(void) { return docFooter; }
			CDocBand * getPageFooter(void) { return pageFooter; }
		private:
			QHash<QString, QFont *> *fonts;
			CDocBand *pageHeader;
			CDocBand *docHeader;
			CDocBand *docBody;
			CDocBand *docFooter;
			CDocBand *pageFooter;
			QSqlDatabase database;
			QString sqlQuery;
			QString lastError;
			QStringList pages;
			int pageWidth, pageHeight;
			
			void createPages(QSqlQuery *query);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CDOCUMENT_H__
//------------------------------------------------------------------------------
