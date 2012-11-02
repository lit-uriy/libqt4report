//------------------------------------------------------------------------------
#ifndef __CREPORT_H__
#define __CREPORT_H__
//------------------------------------------------------------------------------
#include <QFile>
#include <QTranslator>
#include <QSize>
#include <QPainter>
#include <QHash>
#include <QVariant>
//------------------------------------------------------------------------------
namespace libqt4report {
	class CReport {
		public:
			CReport(QString connectionName=QString());
			~CReport(void);
			bool validDocument(QFile *docFile);
			bool process(QFile *docFile);
			int getNbPage(void);
			QString toSvg(int pageIdx);
			QString getLastError(void) { return lastError; }
			QString getLastSourceError(void) { return lastSourceError; }
			QSize getPagesSize(void);
			void renderPage(int pageIdx, QPainter *painter);
			void setParamValue(QString paramName, QVariant value) { params[paramName]=value; }
			
			static QTranslator * getTranslator(void);
		private:
			QString lastError;
			QString lastSourceError;
			QString connectionName;
			QHash<QString, QVariant> params;
			
			void cleanup(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CREPORT_H__
//------------------------------------------------------------------------------