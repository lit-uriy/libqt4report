//------------------------------------------------------------------------------
#include <QVariant>
#include <QtDebug>
#include "CField.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	void CDbFieldObject::process(QSqlRecord *record) {
		QString fieldName=getAttribute("fieldName");

		value=record->value(fieldName).toString();
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------