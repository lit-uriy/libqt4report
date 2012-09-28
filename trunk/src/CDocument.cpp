//------------------------------------------------------------------------------
#include <QtDebug>
#include "CDocument.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	int CDocument::getNbPage(void) {
		return 1;
	}
	
	bool CDocument::render(int pageNo, CPage **page) {
		(*page)=new CPage(210, 297); //TODO xml
		
		return true;
	}
	
	QString CDocument::getLastError(void) {
		return "";
	}
}
//------------------------------------------------------------------------------