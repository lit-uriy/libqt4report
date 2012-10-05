//------------------------------------------------------------------------------
#include <QtDebug>
#include "CDocBand.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	QString CDocBand::toSvg(QSqlRecord *record, int y) {
		QString svg="<g>";
		QHashIterator<QString, CItem *> i(*this);
		
		while (i.hasNext()) {
			i.next();
			svg+=i.value()->toSvg(record, y);
		}
		
		svg+="</g>";
		
		return svg;
	}
	//------------------------------------------------------------------------------
	int CDocBand::getHeight(void) {
		int height=0;
		QHashIterator<QString, CItem *> i(*this);
		
		while (i.hasNext()) {
			int iH;
			i.next();
			
			if((iH=i.value()->getHeight()) > height) {
				height=iH;
			}
		}
		
		return height;
	}
	//------------------------------------------------------------------------------
} //namespace