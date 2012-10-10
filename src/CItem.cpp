//------------------------------------------------------------------------------
#include <QtDebug>
#include <QVariant>
#include "CItem.h"
#include "CFields.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	QString CItemText::toSvg(int &y) {
		return QString("<text x='%1' y='%2' width='%3' height='%4'>%5</text>")
			.arg(attributes.value("x").toInt())
			.arg(attributes.value("y").toInt()+y)
			.arg(attributes.value("width").toInt())
			.arg(attributes.value("height").toInt())
			.arg(getValue());
	}
	//------------------------------------------------------------------------------
	QString CItemTextFieldObject::getValue(void) {
		QString fieldId=attributes.value("fieldId");
		CField *field=CFields::getInstance()->getField(fieldId);
		
		qDebug() << "fieldId" << fieldId << "field" << field;
		
		return field->getValue();
	}
}//namespace
//------------------------------------------------------------------------------