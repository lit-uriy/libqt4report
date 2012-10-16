//------------------------------------------------------------------------------
#include <QtDebug>
#include "CFonts.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	CFonts *CFonts::instance=0;
	//------------------------------------------------------------------------------
	void CFonts::cleanup(void) {
		QHashIterator<QString, CFont *> i(*map);
		while (i.hasNext()) {
			i.next();
			delete i.value();
		}
		delete map;
		delete this;
		
		instance=0;
	}
	//------------------------------------------------------------------------------
	CFonts * CFonts::getInstance(void) {
		if(instance == 0) {
			instance=new CFonts();
		}
		return instance;
	}
	//------------------------------------------------------------------------------
	CFonts::CFonts(void) {
		map=new QHash<QString, CFont *>();
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------