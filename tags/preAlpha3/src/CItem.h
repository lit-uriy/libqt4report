//------------------------------------------------------------------------------
#ifndef __CITEM_H__
#define __CITEM_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QVariant>
#include "CPrintableObject.h"
#include "CValueType.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CItem : public CPrintableObject {
		public:
			virtual ~CItem(void) {}
			void setAttribute(QString name, QString value) { attributes.insert(name, value); }
			QString getAttribute(QString name) { return attributes.value(name) ;}
			bool hasAttribute(QString name) { return attributes.contains(name); }
			virtual int getHeight(void) = 0;
		private:
			QHash<QString ,QString> attributes;
	};
	//------------------------------------------------------------------------------
	class CItemText : public CItem {
		public:
			virtual ~CItemText(void) {}
			QString toSvg(int &y);
			int getHeight(void) { return (int)(getAttribute("y").toDouble()*CPrintableObject::getCoef()); }
		protected:
			virtual QString getValue(void) = 0;
	};
	//------------------------------------------------------------------------------
	class CItemTextFixedObject : public CItemText {
		protected:
			QString getValue(void);
	};
	//------------------------------------------------------------------------------
	class CItemTextFieldObject : public CItemText {
		public:
			~CItemTextFieldObject(void);
			void createValue(QString fieldId);
		protected:
			CValueType *value;
			QString getValue(void);
	};
	//------------------------------------------------------------------------------
	class CItemLineObject : public CItem {
		public:
			QString toSvg(int &y);
			int getHeight(void);
	};
	//------------------------------------------------------------------------------
	class CItemRectObject : public CItemLineObject {
		public:
			QString toSvg(int &y);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CITEM_H__
//------------------------------------------------------------------------------