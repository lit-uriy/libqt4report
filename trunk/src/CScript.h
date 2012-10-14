//------------------------------------------------------------------------------
#ifndef __CSCRIPT_H__
#define __CSCRIPT_H__
//------------------------------------------------------------------------------
#include <QScriptEngine>
#include <QString>
#include "CField.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CScript {
		public:
			static CScript *getInstance(void);
			QVariant eval(CCalculatedFieldObject *field);
		private:
			static CScript *instance;
			QScriptEngine *engine;
			
			CScript(void);
			~CScript(void);
	};
}//namespace
//------------------------------------------------------------------------------
#endif //__CSCRIPT_H__
//------------------------------------------------------------------------------