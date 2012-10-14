//------------------------------------------------------------------------------
#include <QStringList>
#include <QScriptValue>
#include "CScript.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CScript *CScript::instance=0;
	//------------------------------------------------------------------------------
	CScript * CScript::getInstance(void)
	{		
		if(instance == 0) {
			instance=new CScript();
		}
		
		return instance;
	}
	//------------------------------------------------------------------------------
	QVariant CScript::eval(CCalculatedFieldObject *field) {
		int i;
		QString expr=field->getExpression();
		QList<CField *> depends=field->getDepends();

		for(i=0;i<depends.size();i++) {
			CField *field=depends.at(i);
			QString fieldId=field->getAttribute("id");
			
			expr.replace("${"+fieldId+"}", field->getFieldValue().toString());
		}
		
		
		QVariant ret=engine->evaluate(expr).toVariant();
		if(engine->hasUncaughtException()) {
			QStringList errorList=engine->uncaughtExceptionBacktrace() ;
			
			throw new QString("Error while executing "+expr+" : "+errorList.join("\r\n"));
		}
		
		return ret;
	}
	//------------------------------------------------------------------------------
	CScript::CScript(){
		engine=new QScriptEngine();
	}
	//------------------------------------------------------------------------------
	CScript::~CScript() {
		delete engine;
	}
	//------------------------------------------------------------------------------
}//namespace