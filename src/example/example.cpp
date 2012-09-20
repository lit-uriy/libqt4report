//------------------------------------------------------------------------------
#include <QApplication>
#include <libqt4report.h>
#include <iostream>
//------------------------------------------------------------------------------
using std::cout;
using std::endl;
//------------------------------------------------------------------------------
int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Usage: example file [[file] ... ]" << endl;
		return 1;
	}
	
	QApplication app(argc, argv);

	for(int i=1;i<argc;i++) {	
		QFile *xmlFile=new QFile(argv[i]);
		if(xmlFile->open(QIODevice::ReadOnly)) {
			if(libqt4report::validDocument(xmlFile)) {
				cout << argv[i] << " is valid !" << endl;
			}else {
				cout << argv[i] << " is not valid !" << endl;
			}
		}else {
			cout << argv[i] << " not found !" << endl;
		}
		
		delete xmlFile;
	}
	
	return 0;
}
//------------------------------------------------------------------------------