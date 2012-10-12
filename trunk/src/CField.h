//------------------------------------------------------------------------------
#ifndef __CFIELD_H__
#define __CFIELD_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QSqlRecord>
#include <QStringList>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CField {
		public:
			virtual ~CField(void) {}
			void setAttribute(QString name, QString value) { attributes.insert(name, value); }
			QString getAttribute(QString name) { return attributes.value(name); }
			virtual void process(QSqlRecord *record) = 0;
			virtual QString getValue(void) = 0;
			virtual bool isCalculatedField(void) = 0;
			virtual bool isDepend(CField *other) { return false; }
			int compareTo(CField *other);
		protected:
			QHash<QString ,QString> attributes;
	};
	//------------------------------------------------------------------------------
	class CDbFieldObject : public CField {
		public:
			void process(QSqlRecord *record);
			QString getValue(void) { return value; }
			bool isCalculatedField(void) { return false; }
		private:
			QString value;
	};
	//------------------------------------------------------------------------------
	class CCalculatedFieldObject : public CField {
		public:
			void process(QSqlRecord *record);
			QString getValue(void) { return value; }
			void setExpression(QString expression);
			QString getExpression(void) { return expression; }
			bool isCalculatedField(void) { return true; }
			bool isDepend(CField *other);
		private:
			QString value;
			QString expression;
			
			QStringList depends;
	};
	//------------------------------------------------------------------------------
	class CTotalFieldObject : public CField {
		public:
			CTotalFieldObject(void) { value=0; firstTime=true; sum=0; nb=0; }
			void process(QSqlRecord *record);
			QString getValue(void) { return QString::number(value); }
			bool isCalculatedField(void) { return true; }
			bool isDepend(CField *other);
		private:
			double value;
			double sum;
			int nb;
			bool firstTime;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CFIELD_H__
//------------------------------------------------------------------------------