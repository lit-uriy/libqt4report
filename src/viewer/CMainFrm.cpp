//--------------------------------------------------------------------------------------------------------------
#include <QtDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QPaintEngine>
#include <QSvgWidget>
#include <config.h>
#include "CMainFrm.h"
//--------------------------------------------------------------------------------------------------------------
CMainFrm::CMainFrm(QString fileName) : QMainWindow() {
	setupUi(this);
	
	xmlFile=new QFile();
	scrollArea=new QScrollArea(this);
	scrollArea->setAlignment(Qt::AlignCenter);
	
	report=new libqt4report::CReport();
	
	setCentralWidget(scrollArea);
	
	setWindowTitle("viewer - "+QString(PACKAGE_VERSION));
	
	if(!fileName.isEmpty()) {
		loadFile(fileName);
	}
}
//--------------------------------------------------------------------------------------------------------------
CMainFrm::~CMainFrm(void) {
	if(xmlFile->isOpen()) {
		xmlFile->close();
	}
	delete xmlFile;
	delete report;
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::loadFile(QString fileName) {
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
			
			Ui_MainFrm::statusBar->showMessage(fileName);
		}
	}else {
		QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le document"));
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
		loadFile(fileName);
	}
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::on_actionRecharger_triggered(bool) {	
	if(report->process(xmlFile)) {
		QSvgWidget *svgWidget=new QSvgWidget();
		
		svgWidget->load(report->toSvg(0).toUtf8());
	
		scrollArea->setWidget(svgWidget); 
	}else {
		qDebug() << report->getLastError();
	}
}
//--------------------------------------------------------------------------------------------------------------
void CMainFrm::on_actionFermer_triggered(bool) {
	if(xmlFile->isOpen()) {
		xmlFile->close();
	}
	
	Ui_MainFrm::statusBar->clearMessage();
	actionRecharger->setEnabled(false);
	delete scrollArea->widget(); 
	scrollArea->setWidget(0); 
}
//--------------------------------------------------------------------------------------------------------------