//------------------------------------------------------------------------------
#ifndef __CREPORT_H__
#define __CREPORT_H__
//------------------------------------------------------------------------------
#include <QFile>
#include <QImage>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CReport {
		public:
			bool validDocument(QFile *docFile);
			bool render(QFile *docFile, QImage **image);
			QString getLastError(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CREPORT_H__
//------------------------------------------------------------------------------