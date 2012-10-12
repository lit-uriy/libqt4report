//------------------------------------------------------------------------------
#include <QVariant>
#include <QtDebug>
#include <QRegExp>
#include "CField.h"
#include "CFields.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	int CField::compareTo(CField *other) {
		if(!isCalculatedField() && !other->isCalculatedField()) {
			return attributes.value("id").compare(other->getAttribute("id"));
		}
		
		return (isDepend(other) ? 1 : -1);
	}
	//------------------------------------------------------------------------------
	void CDbFieldObject::process(QSqlRecord *record) {
		QString fieldName=getAttribute("fieldName");

		value=record->value(fieldName).toString();
	}
	//------------------------------------------------------------------------------
	bool CCalculatedFieldObject::isDepend(CField *other) {
		int i;
		
		for(i=0;i<depends.size();i++) {
			QString depend=depends.at(i);
			CField *field=CFields::getInstance()->getField(depend);
			if(depend->getAttribute("id") == other->getAttribute("id")) {
				return true;
			}
		}
		
		return false;
	}
	//------------------------------------------------------------------------------
	void CCalculatedFieldObject::process(QSqlRecord *record) {
		int i;
		
		value=expression;
		for(i=0;i<depends.size();i++) {
			QString depend=depends.at(i);
			CField *field=CFields::getInstance()->getField(depend);
			
			value.replace("${"+depend+"}", field->getValue());
		}
	}
	//------------------------------------------------------------------------------
	void CCalculatedFieldObject::setExpression(QString expression) {
		this->expression=expression;
		QRegExp regExp("\\$\\{([a-zA-Z0-9]*)\\}");
		int pos = 0;
		while ((pos = regExp.indexIn(expression, pos)) != -1) {
			pos += regExp.matchedLength();
			depends  << regExp.cap(1);
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
	bool CTotalFieldObject::isDepend(CField *other) {
		return other->getAttribute("id") == getAttribute("fieldId");
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------