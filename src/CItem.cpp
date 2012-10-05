//------------------------------------------------------------------------------
#include <QtDebug>
#include <QVariant>
#include "CItem.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	QString CItemText::toSvg(QSqlRecord *record, int y) {
		return QString("<text x='%1' y='%2' width='%3' height='%4'>%5</text>")
			.arg(attributes.value("x").toInt())
			.arg(attributes.value("y").toInt()+y)
			.arg(attributes.value("width").toInt())
			.arg(attributes.value("height").toInt())
			.arg(getValue(record));
	}
	//------------------------------------------------------------------------------
	QString CItemTextFieldObject::getValue(QSqlRecord *record) {
		QString ret="";
		
		if(record != 0) {
			ret=record->value(attributes.value("fieldName")).toString();
		}
		
		return ret;
	}
}//namespace
//------------------------------------------------------------------------------