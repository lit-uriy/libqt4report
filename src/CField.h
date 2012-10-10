//------------------------------------------------------------------------------
#ifndef __CFIELD_H__
#define __CFIELD_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QSqlRecord>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CField {
		public:
			virtual ~CField(void) {}
			void setAttribute(QString name, QString value) { attributes.insert(name, value); }
			QString getAttribute(QString name) { return attributes.value(name) ;}
			virtual void process(QSqlRecord *record) = 0;
			virtual QString getValue(void) = 0;
		protected:
			QHash<QString ,QString> attributes;
	};
	//------------------------------------------------------------------------------
	class CDbFieldObject : public CField {
		public:
			void process(QSqlRecord *record);
			QString getValue(void) { return value; }
		private:
			QString value;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CFIELD_H__
//------------------------------------------------------------------------------