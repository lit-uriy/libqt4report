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
			virtual QString toSvg(int &y) = 0;
			double static getCoef() { return 90.0/25.6; } //90 dpi 1 pouce = 25.6 mm
			QString static xmlEncode(QString src) { return src.replace("&", "&amp;").replace("\"", "&quot;").replace("'", "&apos;").replace("<", "&lt;").replace(">", "&gt;"); }
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CPRINTABLEOBJECT_H__
//------------------------------------------------------------------------------