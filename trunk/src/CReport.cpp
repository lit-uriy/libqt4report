//------------------------------------------------------------------------------
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>
#include <QBuffer>
#include <QPainter>
#include <QtDebug>
#include "CReport.h"
#include "sch_libqt4report.cpp"
//------------------------------------------------------------------------------
namespace libqt4report {
	bool CReport::validDocument(QFile *docFile) {
		QXmlSchema *xmlSchema=new QXmlSchema();
		bool ret=false;
		
		QByteArray data((const char *)schema_libqt4report_xsd);
		QBuffer buffer(&data);
		buffer.open(QIODevice::ReadOnly);
		
		xmlSchema->load(&buffer);
		if(xmlSchema->isValid()) {
			QXmlSchemaValidator *validator=new QXmlSchemaValidator(*xmlSchema);
			
			if(validator->validate(docFile, QUrl::fromLocalFile(docFile->fileName()))) {
				ret=true;
			}
			
			delete validator;
		}
		
		delete xmlSchema;	
		
		return ret;
	}
	
	bool CReport::render(QFile *docFile, QImage **image) {
		(*image)=new QImage(1230, 1740, QImage::Format_RGB888); //TODO Calculer la taille de l'image en fonction de l'attribut pageSize et des dpi (150 par défaut)
		qDebug() << (*image)->depth();
		(*image)->fill(QColor(Qt::white).rgb());
		QPainter painter(*image);
		
		return true;
	}
	
	QString CReport::getLastError(void) {
		return "";
	}
} //namespace
//------------------------------------------------------------------------------