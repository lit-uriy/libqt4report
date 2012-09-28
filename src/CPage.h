//------------------------------------------------------------------------------
#ifndef __CPAGE_H__
#define __CPAGE_H__
//------------------------------------------------------------------------------
#include <QImage>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CPage {
		public:
			CPage(int pageWidth, int pageHeight);
			QByteArray toSVG(void) const;
			QString getLastError(void);
		private:
			int pageWidth, pageHeight;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CPAGE_H__
//------------------------------------------------------------------------------