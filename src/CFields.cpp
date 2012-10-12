//------------------------------------------------------------------------------
#include <QtDebug>
#include "CFields.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CFields *CFields::instance=0;
	//------------------------------------------------------------------------------
	CField * CFields::getField(QString key) { 
		return map->at(keyMap->value(key)); 
	}
	//------------------------------------------------------------------------------
	void CFields::addField(QString key, CField *field) {
		int nextIdx=map->size();
		keyMap->insert(key, nextIdx);
		map->append(field); 
	}
	//------------------------------------------------------------------------------
	bool CFields::sort(void) {
		return true;
	}
	//------------------------------------------------------------------------------
	void CFields::process(QSqlRecord *record) {
		int i;
		
		for(i=0;i<map->size();i++) {
			map->at(i)->process(record);
		}
	}
	//------------------------------------------------------------------------------
	CFields * CFields::getInstance(void) {
		if(instance == 0) {
			instance=new CFields();
		}
		return instance;
	}
	//------------------------------------------------------------------------------
	CFields::CFields(void) {
		map=new QList<CField *>();
		keyMap=new QHash<QString, int>();
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------