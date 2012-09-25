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
			bool validDocument(QFile *docFile);
			bool process(QFile *docFile, CDocument **document);
			QString getLastError(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CREPORT_H__
//------------------------------------------------------------------------------