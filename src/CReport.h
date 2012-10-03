//------------------------------------------------------------------------------
#ifndef __CREPORT_H__
#define __CREPORT_H__
//------------------------------------------------------------------------------
#include <QFile>
#include "CDocument.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CReport {
		public:
			CReport(void);
			bool validDocument(QFile *docFile);
			bool process(QFile *docFile, CDocument **document);
			QString getLastError(void) { return lastError; }
		private:
			QString lastError;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CREPORT_H__
//------------------------------------------------------------------------------