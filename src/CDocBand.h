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
			QString toSvg(int &y);
			int getHeight(void);
			void cleanup(void);
		private:
			int height;
	};
} //namespace
//------------------------------------------------------------------------------
#endif //__CDOCBAND_H__
//------------------------------------------------------------------------------