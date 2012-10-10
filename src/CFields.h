//------------------------------------------------------------------------------
#ifndef __CFIELDS_H__
#define __CFIELDS_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QSqlRecord>
#include "CField.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CFields {
		public:
			CField * getField(QString key) { return map->value(key); }
			void addField(QString key, CField *field) { map->insert(key, field); }
			void process(QSqlRecord *record);
			static CFields * getInstance(void);
		private:
			static CFields *instance;
			QHash<QString, CField *> *map;
			
			CFields(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CFIELD_H__
//------------------------------------------------------------------------------