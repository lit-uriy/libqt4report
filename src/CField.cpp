//------------------------------------------------------------------------------
#include <QVariant>
#include <QtDebug>
#include <QRegExp>
#include "CField.h"
#include "CFields.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	void CDbFieldObject::process(QSqlRecord *record) {
		QString fieldName=getAttribute("fieldName");

		value=record->value(fieldName).toString();
	}
	//------------------------------------------------------------------------------
	void CCalculatedFieldObject::process(QSqlRecord *record) {
		int i;
		
		value=expression;
		for(i=0;i<depends.size();i++) {
			CField *field=depends.at(i);
			
			value.replace("${"+field->getAttribute("id")+"}", field->getValue());
		}
	}
	//------------------------------------------------------------------------------
	void CCalculatedFieldObject::setExpression(QString expression) {
		this->expression=expression;
		QRegExp regExp("\\$\\{([a-zA-Z0-9]*)\\}");
		int pos = 0;
		while ((pos = regExp.indexIn(expression, pos)) != -1) {
			QString fieldId=regExp.cap(1);
			pos += regExp.matchedLength();
			CField *field=CFields::getInstance()->getField(fieldId);
			
			if(field == 0) {
				throw new QString("Field "+fieldId+" not exists !");
				return;
			}
			depends << field;
		}
	}
	//------------------------------------------------------------------------------
	void CTotalFieldObject::process(QSqlRecord *record) {
		CField *field=CFields::getInstance()->getField(getAttribute("fieldId"));
		QString operation=getAttribute("operation");
		double fValue=field->getValue().toDouble();
		
		if(operation == "sum") {
			value+=fValue;
		}else if(operation == "avg") {
			sum+=fValue;
			nb++;
			value=sum/nb;
		}else if(operation == "count") {
			value++;
		}else if(operation == "min") {
			if(fValue < value || firstTime) {
				value=fValue;
				firstTime=false;
			}
		}else if(operation == "max") {
			if(fValue > value) {
				value=fValue;
			}
		}
	}
	//------------------------------------------------------------------------------
	const QList<CField *> CTotalFieldObject::getDepends(void) {
		QList<CField *> depend;
		CField *field=CFields::getInstance()->getField(getAttribute("fieldId"));
		
		depend << field;
		
		return depend;
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------