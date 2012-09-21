//--------------------------------------------------------------------------------------------------------------
#include <QtDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <config.h>
#include <libqt4report.h>
#include "CMainFrm.h"
//--------------------------------------------------------------------------------------------------------------
CMainFrm::CMainFrm(void) : QMainWindow() {
	setupUi(this);
	
	xmlFile=new QFile();
	scrollArea=new QScrollArea(this);
	
	setCentralWidget(scrollArea);
	
	setWindowTitle("viewer - "+QString(PACKAGE_VERSION));
}
//--------------------------------------------------------------------------------------------------------------
CMainFrm::~CMainFrm(void) {
	if(xmlFile->isOpen()) {
		xmlFile->close();
	}
	delete xmlFile;
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
			if(!libqt4report::validDocument(xmlFile)) {
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
	scrollArea->setWidget(libqt4report::render(xmlFile)); 
}
//--------------------------------------------------------------------------------------------------------------