//--------------------------------------------------------------------------------------------------------------
#include <QtDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QPaintEngine>
#include <QLabel>
#include <config.h>
#include "CMainFrm.h"
//--------------------------------------------------------------------------------------------------------------
CMainFrm::CMainFrm(void) : QMainWindow() {
	setupUi(this);
	
	xmlFile=new QFile();
	scrollArea=new QScrollArea(this);
	scrollArea->setAlignment(Qt::AlignCenter);
	
	report=new libqt4report::CReport();
	document=0;
	
	setCentralWidget(scrollArea);
	
	setWindowTitle("viewer - "+QString(PACKAGE_VERSION));
}
//--------------------------------------------------------------------------------------------------------------
CMainFrm::~CMainFrm(void) {
	if(xmlFile->isOpen()) {
		xmlFile->close();
	}
	delete xmlFile;
	delete report;
	
	if(document != 0) {
		delete document;
	}
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::on_actionQuitter_triggered(bool) {
	close();
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::on_actionOuvrir_triggered(bool) {
	QString fileName=QFileDialog::getOpenFileName(this, tr("Ouvrir"), QDir::home().path(), tr("Fichier xlqr (*.xlqr)"));
	
	if(!fileName.isEmpty()) {
		if(xmlFile->isOpen()) {
			xmlFile->close();
		}
		
		xmlFile->setFileName(fileName);
		
		if(xmlFile->open(QIODevice::ReadOnly)) {
			if(!report->validDocument(xmlFile)) {
				QMessageBox::critical(this, tr("Erreur de validation"), tr("Impossible de valider le document, êtes-vous sûre qu'il sagisse d'un document lxqr ?"));
			}else {
				xmlFile->seek(0);
				actionRecharger->setEnabled(true);
			}
		}else {
			QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le document"));
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::on_actionRecharger_triggered(bool) {
	if(document != 0) {
		delete document;
	}
	
	if(report->process(xmlFile, &document)) {
		libqt4report::CPage *page;
		
		if(document->render(0, &page)) {
			QLabel *lbl=new QLabel();
		
			lbl->setPixmap(QPixmap::fromImage(page->toImage()));
	
			scrollArea->setWidget(lbl); 
		}
	}
}
//--------------------------------------------------------------------------------------------------------------