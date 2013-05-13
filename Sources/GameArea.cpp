/*************************************************************
* The GameArea class draws the background, paddles, and ball
* typical of a pong court. Its setters are convenience
* functions that handle calling -setNeedsDisplayInRect.
* The PongView also handles tracking whether the up/down
* arrow keys are depressed.
************************************************************/

#include "GameArea.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

#include "ProgrammedObjects/ProgrammedObject.h"
#include "pongai.h"

GameArea::GameArea(QWidget *parent) : QWidget(parent)
{
	this->setFocusPolicy(Qt::StrongFocus);

	_leftPaddle = new ProgrammedObject(this);
	_rightPaddle = new ProgrammedObject(this);
	_ball = new ProgrammedObject(this);
}

void GameArea::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QRect paintRect = event->rect();

	painter.fillRect(paintRect, Qt::black);

	painter.fillRect(_leftPaddle->rect(), Qt::white);

	painter.fillRect(_rightPaddle->rect(), Qt::white);

	painter.setBrush(QBrush(Qt::white));
	painter.drawEllipse(_ball->rect());
}

/* Tracks which key is depressed. */
void GameArea::keyPressEvent(QKeyEvent *event)
{
	int keyCode = event->key();

	switch(keyCode)
	{
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Space:
		{
			_lastKeyCode = keyCode;
			break;
		}
		default:
		{
			QWidget::keyPressEvent(event);
			break;
		}
	};
}

void GameArea::keyReleaseEvent(QKeyEvent *event)
{
	int keyCode = event->key();

	switch(keyCode)
	{
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Space:
		{
			if (keyCode == _lastKeyCode)
			{
				_lastKeyCode = 0;
			}
			break;
		}
		default:
		{
			QWidget::keyPressEvent(event);
			break;
		}
	};
}

void GameArea::resizeEvent(QResizeEvent *event)
{
	this->reset();
}

void GameArea::setScript(QString script)
{
	_rightPaddle->setScript(script);
	_leftPaddle->setScript(script);
	reset();
}

/* Returns all shapes to their starting positions and allocates a new AI. */
void GameArea::reset()
{
	QRect rect;

	rect = QRect(this->rect().width()/2,10,20,20);
	_ball->setRect(rect);

	rect = QRect(1,50,10,99);
	_leftPaddle->setRect(rect);
	_leftPaddle->reset();

	rect = QRect(this->rect().width() - 10,50,10,99);
	_rightPaddle->setRect(rect);
	_rightPaddle->reset();

	_deltaX = -kUpdateDistance;
	_deltaY = -kUpdateDistance;
}

void GameArea::update()
{
	// Spacebar
	if (Qt::Key_Space == _lastKeyCode)
	{
		this->reset();
		return;
	}

	// Exit off left side of screen
	if (_ball->right() < this->rect().left())
	{
		this->reset();
		return;
	}

	// Exit off right side of screen
	if (_ball->left() > this->rect().right())
	{
		this->reset();
		return;
	}

	_rightPaddle->update(_ball, this->rect());
	_leftPaddle->update(_ball, this->rect());

	// Bounce off bottom of screen
	if (_ball->bottom() <= this->rect().bottom() + 1)
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

	this->repaint();
}
