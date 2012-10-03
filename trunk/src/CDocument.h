//------------------------------------------------------------------------------
#ifndef __CDOCUMENT_H__
#define __CDOCUMENT_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QFont>
#include <QSqlDatabase>
#include "CPage.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CDocument {
		public:
			CDocument(void);
			int getNbPage(void);
			bool render(int pageNo, CPage **page);
			QString getLastError(void) { return lastError; }
			void addFont(QString id, QFont *font) { fonts->insert(id, font); }
			QFont *getFont(QString id) { return fonts->value(id); }
			void setDatabaseInfos(QString driver, QString host, QString userName, QString password, QString dbName);
			void setQuery(QString sqlQuery) { this->sqlQuery=sqlQuery.trimmed(); }
			bool process(void);
		private:
			QHash<QString, QFont *> *fonts;
			QSqlDatabase database;
			QString sqlQuery;
			QString lastError;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CDOCUMENT_H__
//------------------------------------------------------------------------------