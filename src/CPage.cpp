//------------------------------------------------------------------------------
#include <QtDebug>
#include <QColor>
#include <QPainter>
#include "CPage.h"
//------------------------------------------------------------------------------
#define DPI				100
#define INCH			25.6
#define COEF			((double)DPI/INCH)
//------------------------------------------------------------------------------
namespace libqt4report {
	CPage::CPage(int pageWidth, int pageHeight) {
		this->pageWidth=pageWidth;
		this->pageHeight=pageHeight;
	}
	
	QImage CPage::toImage(void) const {
		QImage image(pageWidth*COEF, pageHeight*COEF, QImage::Format_RGB888); 
		
		image.fill(QColor(Qt::white).rgb());
		QPainter painter(&image);
		
		return image;
	}
	
	QString CPage::getLastError(void) {
		return "";
	}
}
//------------------------------------------------------------------------------