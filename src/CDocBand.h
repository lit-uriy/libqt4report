//------------------------------------------------------------------------------
#ifndef __CDOCBAND_H__
#define __CDOCBAND_H__
//------------------------------------------------------------------------------
#include <QHash>
#include <QSqlRecord>
#include "CPrintableObject.h"
#include "CItem.h"
//------------------------------------------------------------------------------
namespace libqt4report {
	class CDocBand : public CPrintableObject, public QHash<QString, CItem *> {
		public:
			QString toSvg(QSqlRecord *record, int y);
			int getHeight(void);
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CDOCBAND_H__
//------------------------------------------------------------------------------