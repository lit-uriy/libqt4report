//------------------------------------------------------------------------------
#ifndef __CDOCUMENTPARSER_H__
#define __CDOCUMENTPARSER_H__
//------------------------------------------------------------------------------
#include <QXmlDefaultHandler>
#include "CDocument.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CDocumentParser : public QXmlDefaultHandler {
		public:
			bool startDocument(void);
			bool endDocument(void);
			bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
			bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
			bool characters(const QString& ch);
			CDocument *getDocument(void) { return document; }
		private:
			CDocument *document;
			bool inFonts;
			bool inDatabase;
			bool inQuery;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CDOCUMENTPARSER_H__
//------------------------------------------------------------------------------