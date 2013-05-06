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
#define kUpdateDistance 4

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

	_leftPaddle = new ProgrammedObject(this);
	_rightPaddle = new ProgrammedObject(this);
	_ball = new ProgrammedObject(this);
	_court = new ProgrammedObject(this);

	_pongWidget->setFocus();

	this->resize(550,350);

	// Begin game.
	this->reset();
}

MainWindow::~MainWindow()
{
}

/* Returns all shapes to their starting positions and allocates a new AI. */
void MainWindow::reset()
{
	QRect rect;
	QRect courtRect = _pongWidget->rect();

	_court->setRect(courtRect);

	rect = QRect(courtRect.width()/2,10,20,20);
	_ball->setRect(rect);

	rect = QRect(1,50,10,99);
	_leftPaddle->setRect(rect);

	rect = QRect(courtRect.width() - 10,50,10,99);
	_rightPaddle->setRect(rect);

	_deltaX = -kUpdateDistance;
	_deltaY = -kUpdateDistance;

	_pongWidget->setBallRect(_ball->rect());
	_pongWidget->setLeftPaddleRect(_leftPaddle->rect());
	_pongWidget->setRightPaddleRect(_rightPaddle->rect());

	_pongAI = new PongAI(_textEdit->toPlainText(), this);

}

/* Moves paddles and ball. (Called on a timer.) */
void MainWindow::slotUpdate()
{
	int keyCode = _pongWidget->lastKeyCode();

	// Spacebar
	if (Qt::Key_Space == keyCode)
	{
		this->reset();
		return;
	}

	// Exit off left side of screen
	if (_ball->right() < _court->left())
	{
		this->reset();
		return;
	}

	// Exit off right side of screen
	if (_ball->left() > _court->right())
	{
		this->reset();
		return;
	}

	// Move human paddle
	if (Qt::Key_Up == keyCode)
	{
		if (_leftPaddle->top() > 0)
		{
			_leftPaddle->moveY(-kUpdateDistance);
		}
		_pongWidget->setLeftPaddleRect(_leftPaddle->rect());
	}
	else if (Qt::Key_Down == keyCode)
	{
		if (_leftPaddle->bottom() < _court->bottom())
		{
			_leftPaddle->moveY(kUpdateDistance);
		}
		_pongWidget->setLeftPaddleRect(_leftPaddle->rect());
	}

	// Move AI paddle
	Direction direction = _pongAI->nextMove(_rightPaddle, _ball);
	if (direction == kUpDirection)
	{
		if (_rightPaddle->top() > 0)
		{
			_rightPaddle->moveY(-kUpdateDistance);
		}
		_pongWidget->setRightPaddleRect(_rightPaddle->rect());
	}
	else if (direction == kDownDirection)
	{
		if (_rightPaddle->bottom() < _court->bottom())
		{
			_rightPaddle->moveY(kUpdateDistance);
		}
		_pongWidget->setRightPaddleRect(_rightPaddle->rect());
	}

	// Bounce off bottom of screen
	if (_ball->bottom() <= _court->bottom() + 1)
	{
		_deltaY = -_deltaY;
	}

	// Bounce off top of screen
	if (_ball->top() >= 0)
	{
		_deltaY = -_deltaY;
	}

	// Bounce off left paddle
	if (_ball->intersects(_leftPaddle->rect()))
	{
		_deltaX = -_deltaX;
		if (_ball->middleY() > _leftPaddle->top() - (_leftPaddle->height() / 5))
		{
			// top fifth
			_deltaY += kUpdateDistance;
			if (_deltaY == 0)
			{
				_deltaY = kUpdateDistance;
			}
		}
		else if (_ball->middleY() < _leftPaddle->bottom() + (_leftPaddle->height() / 5))
		{
			// bottom fifth
			_deltaY -= kUpdateDistance;
			if (_deltaY == 0)
			{
				_deltaY = -kUpdateDistance;
			}
		}
	}

	// Bounce off right paddle
	if (_ball->intersects(_rightPaddle->rect()))
	{
		_deltaX = -_deltaX;

		if (_ball->middleY() < _rightPaddle->bottom() + (_rightPaddle->height() / 5))
		{
			// bottom fifth
			_deltaY -= kUpdateDistance;
			if (_deltaY == 0)
			{
				_deltaY = -kUpdateDistance;
			}
		}
		else if(_ball->middleY() > _rightPaddle->top() - (_rightPaddle->height() / 5))
		{
			// top fifth
			_deltaY += kUpdateDistance;
			if (_deltaY == 0)
			{
				_deltaY = kUpdateDistance;
			}
		}
	}

	// Move ball
	_ball->moveX(_deltaX);
	_ball->moveY(_deltaY);

	_pongWidget->setBallRect(_ball->rect());
	_pongWidget->repaint();
}

void MainWindow::slotTabDidChange(int tabIndex)
{
	if (kPongWidgetIndex == tabIndex)
	{
		this->reset();
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
