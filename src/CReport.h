//------------------------------------------------------------------------------
#ifndef __CREPORT_H__
#define __CREPORT_H__
//------------------------------------------------------------------------------
#include <QFile>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CReport {
		public:
			CReport(void);
			~CReport(void);
			bool validDocument(QFile *docFile);
			bool process(QFile *docFile);
			int getNbPage(void);
			QString toSvg(int pageIdx);
			QString getLastError(void) { return lastError; }
		private:
			QString lastError;
			
			void cleanup(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CREPORT_H__
//------------------------------------------------------------------------------