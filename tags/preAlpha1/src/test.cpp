#include <QApplication>
#include <CReport.h>
#include <QtDebug>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
	void *array[10];
	size_t size;
	
	size=backtrace(array, 10);
	
	fprintf(stderr, "Error: signl %d:\n", sig);
	backtrace_symbols_fd(array, size, 2);
	exit(1);
}

void process(char *filename) {
	QFile *xmlFile=new QFile(filename);
	if(xmlFile->open(QIODevice::ReadOnly)) {
		int i;
		libqt4report::CReport *report=new libqt4report::CReport();
		
		for(i=0;i<100000;i++) {
			qDebug() << "---------- Process ----------" << i;
			xmlFile->seek(0);
			report->process(xmlFile);
		}
		
		delete report;
	}
	delete xmlFile;
}

int main(int argc, char *argv[]) {
	if(argc == 2) {
		QApplication app(argc, argv);
		
		signal(SIGSEGV, handler);
		process(argv[1]);
	}
}