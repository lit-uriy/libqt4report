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
			QVariant getFieldValue(void);
			void resetPoid(void) { poid=0; }
			void decPoid(void) { poid--; }
			int getPoid(void) { return poid; }
			virtual const QList<CField *> getDepends(void) { return QList<CField *>(); }
		protected:
			QHash<QString ,QString> attributes;
			int poid;
			
			virtual QString getValue(void) = 0;
	};
	//------------------------------------------------------------------------------
	class CDbFieldObject : public CField {
		public:
			void process(QSqlRecord *record);
		private:
			QString value;
			
			QString getValue(void) { return value; }
	};
	//------------------------------------------------------------------------------
	class CCalculatedFieldObject : public CField {
		public:
			void process(QSqlRecord *record);
			void setExpression(QString expression);
			QString getExpression(void) { return expression; }
			const QList<CField *> getDepends(void) { return depends; }
		private:
			QString value;
			QString expression;
			QList<CField *> depends;
			
			QString getValue(void) { return value; }
	};
	//------------------------------------------------------------------------------
	class CTotalFieldObject : public CField {
		public:
			CTotalFieldObject(void) { value=0; firstTime=true; sum=0; nb=0; }
			void process(QSqlRecord *record);
			const QList<CField *> getDepends(void);
		private:
			double value;
			double sum;
			int nb;
			bool firstTime;
			
			QString getValue(void) { return QString::number(value); }
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CFIELD_H__
//------------------------------------------------------------------------------