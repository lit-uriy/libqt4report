//------------------------------------------------------------------------------
#ifndef __CPRINTABLEOBJECT_H__
#define __CPRINTABLEOBJECT_H__
//------------------------------------------------------------------------------
#include <QSqlRecord>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CPrintableObject {
		public:
			virtual ~CPrintableObject(void) {}
			virtual QString toSvg(QSqlRecord *record, int y) = 0;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CPRINTABLEOBJECT_H__
//------------------------------------------------------------------------------