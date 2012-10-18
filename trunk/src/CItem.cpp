//------------------------------------------------------------------------------
#include <QtDebug>
#include <QVariant>
#include <QDate>
#include "CItem.h"
#include "CFields.h"
#include "CFonts.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	QString CItemText::toSvg(int &y) {
		double coef=CPrintableObject::getCoef();
		QString value=CPrintableObject::xmlEncode(getValue().toString());
		QString align="";
		QString style="style='";
		CFont *font=CFonts::getInstance()->getFont(attributes.value("fontId"));
		QString color;
		
		if(attributes.contains("color")) {
			color="stroke:"+attributes.value("color")+";fill:"+attributes.value("color")+";";
		}
		
		style+="font-family:"+font->getFamily()+";font-size:"+QString::number(font->getSize())+"pt;";
		style+="font-weight:"+font->getWeight()+";";
		style+="font-style:"+font->getStyle()+";";
		style+=color+"'";
		
		if(attributes.contains("align")) {
			align="text-anchor='"+attributes.value("align")+"'";
		}
		
		return QString("<text x='%1' y='%2' "+align+" "+style+">%3</text>")
			.arg((int)(attributes.value("x").toDouble()*coef))
			.arg((int)((attributes.value("y").toDouble())*coef)+y)
			.arg(value);
	}
	//------------------------------------------------------------------------------
	QVariant CItemTextFieldObject::getValue(void) {
		QString fieldId=attributes.value("fieldId");
		CField *field=CFields::getInstance()->getField(fieldId);
		
		return field->getFieldValue();
	}
	//------------------------------------------------------------------------------
	QString CItemLineObject::toSvg(int &y) {
		double coef=CPrintableObject::getCoef();
		int height=(int)((attributes.value("height").toDouble())*coef);
		int x1, y1, x2, y2;
		QString color="black";
		
		x1=(int)(attributes.value("x").toDouble()*coef);
		y1=(int)((attributes.value("y").toDouble())*coef)+y;
		x2=x1+(int)(attributes.value("width").toDouble()*coef);
		y2=y1+height;
		
		if(attributes.contains("color")) {
			color=attributes.value("color");
		}
		
		return QString("<line x1='%1' y1='%2' x2='%3' y2='%4' style='stroke:"+color+";stroke-width:1;' />")
			.arg(x1).arg(y1).arg(x2).arg(y2);
	}
	//------------------------------------------------------------------------------
	int CItemLineObject::getHeight(void) { 
		double coef=CPrintableObject::getCoef();
		int y, height;
		
		y=(int)((attributes.value("y").toDouble())*coef);
		height=(int)((attributes.value("height").toDouble())*coef);
		
		return y+height;
	}
	//------------------------------------------------------------------------------
	QString CItemRectObject::toSvg(int &y) {
		double coef=CPrintableObject::getCoef();
		int x, yR, width, height;
		QString color="black";
		
		x=(int)(attributes.value("x").toDouble()*coef);
		yR=(int)((attributes.value("y").toDouble())*coef)+y;
		width=(int)(attributes.value("width").toDouble()*coef);
		height=(int)((attributes.value("height").toDouble())*coef);
		
		if(attributes.contains("color")) {
			color=attributes.value("color");
		}
		
		return QString("<rect x='%1' y='%2' width='%3' height='%4' style='stroke:"+color+";stroke-width:1;fill:none;' />")
		.arg(x).arg(yR).arg(width).arg(height);
	}
	//------------------------------------------------------------------------------
}//namespace
//------------------------------------------------------------------------------