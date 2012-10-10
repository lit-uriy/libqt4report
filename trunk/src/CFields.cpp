//------------------------------------------------------------------------------
#include <QtDebug>
#include "CFields.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CFields *CFields::instance=0;
	//------------------------------------------------------------------------------
	void CFields::process(QSqlRecord *record) {
		QHashIterator<QString, CField *> i(*map);
	
		while (i.hasNext()) {
			i.next();
			i.value()->process(record);
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
		map=new QHash<QString, CField *>();
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------