//------------------------------------------------------------------------------
#ifndef __CITEM_H__
#define __CITEM_H__
//------------------------------------------------------------------------------
#include <QHash>
#include "CPrintableObject.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CItem : public CPrintableObject {
		public:
			virtual ~CItem(void) {}
			void setAttribute(QString name, QString value) { attributes.insert(name, value); }
			QString getAttribute(QString name) { return attributes.value(name) ;}
			virtual int getHeight(void) = 0;
		protected:
			QHash<QString ,QString> attributes;
	};
	//------------------------------------------------------------------------------
	class CItemText : public CItem {
		public:
			virtual ~CItemText(void) {}
			QString toSvg(QSqlRecord *record, int y);
			int getHeight(void) { return attributes.value("y").toInt(); }
		protected:
			virtual QString getValue(QSqlRecord *record) = 0;
	};
	//------------------------------------------------------------------------------
	class CItemTextFixedObject : public CItemText {
		protected:
			QString getValue(QSqlRecord *record) { return attributes.value("value"); }
	};
	//------------------------------------------------------------------------------
	class CItemTextFieldObject : public CItemText {
		protected:
			QString getValue(QSqlRecord *record);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CITEM_H__
//------------------------------------------------------------------------------