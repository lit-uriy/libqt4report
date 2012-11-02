//------------------------------------------------------------------------------
#ifndef __CPRINTABLEOBJECT_H__
#define __CPRINTABLEOBJECT_H__
//------------------------------------------------------------------------------
#include <QPainter>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CRendererObject {
		public:
			virtual void draw(QPainter *) = 0;
	};
	//------------------------------------------------------------------------------
	class CPrintableObject {
		public:
			virtual ~CPrintableObject(void) {}
			virtual QString toSvg(int y, double coef) = 0;
			virtual void prepareRender(QList<CRendererObject *> *rendererObjects, double coef) = 0;
			QString xmlEncode(QString src) { return src.replace("&", "&amp;").replace("\"", "&quot;").replace("'", "&apos;").replace("<", "&lt;").replace(">", "&gt;"); }
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CPRINTABLEOBJECT_H__
//------------------------------------------------------------------------------