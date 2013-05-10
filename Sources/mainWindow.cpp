/*************************************************************
* The MainWindow class moves the paddles and ball around
* the screen on a timer.
************************************************************/

#include "mainWindow.h"

#include <QTextEdit>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QSplitter>
#include <QListWidget>

#include "ProgrammedObjects/ProgrammedObject.h"
#include "pongwidget.h"
#include "pongai.h"

#include <QDebug>

//Constants
#define kUpdateInterval 30

// Implementation
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags)
{
	QSplitter *splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Horizontal);
	this->setCentralWidget(splitter);

	_pongWidget = new PongWidget(this);
	splitter->addWidget(_pongWidget);

	QSplitter *rightPanel = new QSplitter(this);
	rightPanel->setOrientation(Qt::Vertical);
	splitter->addWidget(rightPanel);

	_objectsList = new QListWidget(this);
	rightPanel->addWidget(_objectsList);

	_textEdit = new QTextEdit(this);
	rightPanel->addWidget(_textEdit);

	QFile file(":PongAI.js");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString lines  = in.readAll();
	_textEdit->setText(lines);

	connect(_textEdit, SIGNAL(textChanged()),
		this, SLOT(slotTextChanged()));

	_timer = new QTimer(this);
	connect(_timer, SIGNAL(timeout()), this, SLOT(slotUpdate()));
	_timer->start(kUpdateInterval);

	_pongWidget->setFocus();

	this->resize(550,350);

	// Begin game.
	_pongWidget->reset(_textEdit->toPlainText());
}

MainWindow::~MainWindow()
{
}

/* Moves paddles and ball. (Called on a timer.) */
void MainWindow::slotUpdate()
{
	_pongWidget->update();
}

void MainWindow::slotTextChanged()
{
	_pongWidget->reset(_textEdit->toPlainText());
	_timer->start(kUpdateInterval);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	this->update();
}
