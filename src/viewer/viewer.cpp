//------------------------------------------------------------------------------
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QDir>
#include <config.h>
#include "CMainFrm.h"
//------------------------------------------------------------------------------
int main(int argc, char **argv) {
	QTranslator translator;
	int ret;
	QApplication app(argc, argv);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
	
	translator.load("viewer"+QLocale::system().name(), QDir(QString(DATADIR)).absolutePath());
	
	app.installTranslator(&translator);
	
	app.setApplicationName("viewer");
	app.setApplicationVersion(PACKAGE_VERSION);
	
	CMainFrm *mainFrm=new CMainFrm();
	mainFrm->showMaximized();

	ret=app.exec();
	
	return ret;
}
//------------------------------------------------------------------------------