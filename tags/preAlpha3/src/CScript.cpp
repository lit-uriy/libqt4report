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
			QScriptValue obj=engine->newVariant(field->getFieldValue());
			engine->globalObject().setProperty(fieldId, obj);
			
			expr.replace("${"+fieldId+"}", "this."+fieldId);
		}
		
		
		QVariant ret=engine->evaluate(expr).toVariant();
		if(engine->hasUncaughtException()) {
			QStringList errorList=engine->uncaughtExceptionBacktrace() ;
			
			throw new QString("Error while executing "+expr+" : "+errorList.join("\r\n"));
		}
		
		return ret;
	}
	//------------------------------------------------------------------------------
	void CScript::cleanup(void) {
		delete this;
		instance=0;
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