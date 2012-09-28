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
	
	QString CPage::toSVG(void) {
		int w=pageWidth*COEF, h=pageHeight*COEF;
		QString svg="<?xml version='1.0' encoding='utf-8'?>\
		<svg xmlns='http://www.w3.org/2000/svg' version='1.2' \
		baseProfile='tiny' width='"+QString::number(w)+"' \
		height='"+QString::number(h)+"'>";
		
		svg+="<rect x='0' y='0' width='"+QString::number(w)+"' height='"+QString::number(h)+"' fill='white' stroke='none' />";
		
		svg+="</svg>";
		
		return svg;
	}
	
	QString CPage::getLastError(void) {
		return "";
	}
}
//------------------------------------------------------------------------------