//------------------------------------------------------------------------------
#ifndef __CFIELDS_H__
#define __CFIELDS_H__
//------------------------------------------------------------------------------
#include <QList>
#include <QHash>
#include <QSqlRecord>
#include "CField.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CFields {
		public:
			CField * getField(QString key);
			void addField(QString key, CField *field);
			void process(QSqlRecord *record);
			bool sort(void);
			QString getSortError(void) { return sortError; }
			static CFields * getInstance(void);
		private:
			static CFields *instance;
			QList<CField *> *map;
			QHash<QString, int> *keyMap;
			QString sortError;
			
			CFields(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CFIELD_H__
//------------------------------------------------------------------------------