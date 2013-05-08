/*************************************************************
* The MainWindow class moves the paddles and ball around
* the screen on a timer.
************************************************************/

#include "mainWindow.h"
#include <QTableWidget>
#include <QTextEdit>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "ProgrammedObjects/ProgrammedObject.h"
#include "pongwidget.h"
#include "pongai.h"

#include <QDebug>

//Constants

enum
{
	kPongWidgetIndex = 0,
	kAIScriptWidgetIndex
};

#define kUpdateInterval 30

// Implementation
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags)
{
	QTabWidget *tabWidget = new QTabWidget(this);
	this->setCentralWidget(tabWidget);

	_pongWidget = new PongWidget(this);
	tabWidget->insertTab(kPongWidgetIndex, _pongWidget, tr("Pong"));

	_textEdit = new QTextEdit(this);
	tabWidget->insertTab(kAIScriptWidgetIndex, _textEdit, tr("AI script"));

	QFile file(":PongAI.js");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString lines  = in.readAll();
	_textEdit->setText(lines);

	connect(tabWidget, SIGNAL(currentChanged(int)),
		this, SLOT(slotTabDidChange(int)));

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

void MainWindow::slotTabDidChange(int tabIndex)
{
	if (kPongWidgetIndex == tabIndex)
	{
		_pongWidget->reset(_textEdit->toPlainText());
		_timer->start(kUpdateInterval);
	}
	else if (kAIScriptWidgetIndex == tabIndex)
	{
		_timer->stop();
	}
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	this->update();
}
