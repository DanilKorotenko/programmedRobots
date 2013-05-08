/*************************************************************
* The PongWidget class draws the background, paddles, and ball
* typical of a pong court. Its setters are convenience
* functions that handle calling -setNeedsDisplayInRect.
* The PongView also handles tracking whether the up/down
* arrow keys are depressed.
************************************************************/

#include "pongwidget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

#include "ProgrammedObjects/ProgrammedObject.h"
#include "pongai.h"

#define kUpdateDistance 4

PongWidget::PongWidget(QWidget *parent) : QWidget(parent)
{
	this->setFocusPolicy(Qt::StrongFocus);

	_leftPaddle = new ProgrammedObject(this);
	_rightPaddle = new ProgrammedObject(this);
	_ball = new ProgrammedObject(this);
	_court = new ProgrammedObject(this);

}

QRect PongWidget::leftPaddleRect()
{
	return _leftPaddleRect;
}

void PongWidget::setLeftPaddleRect(QRect value)
{
	if (_leftPaddleRect != value)
	{
		_leftPaddleRect = value;
	}
}

QRect PongWidget::rightPaddleRect()
{
	return _rightPaddleRect;
}

void PongWidget::setRightPaddleRect(QRect value)
{
	if (_rightPaddleRect != value)
	{
		_rightPaddleRect = value;
	}
}

QRect PongWidget::ballRect()
{
	return _ballRect;
}

void PongWidget::setBallRect(QRect value)
{
	if (_ballRect != value)
	{
		_ballRect.setRect(value.x(), value.y(), value.width(),value.height());
	}
}

/* Tracks which key is depressed. */

int PongWidget::lastKeyCode()
{
	return _lastKeyCode;
}

void PongWidget::setLastKeyCode(int keyCode)
{
	if (_lastKeyCode != keyCode)
	{
		_lastKeyCode = keyCode;
	}
}

void PongWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QRect paintRect = event->rect();

	painter.fillRect(paintRect, Qt::black);

	painter.fillRect(_leftPaddleRect, Qt::white);

	painter.fillRect(_rightPaddleRect, Qt::white);

	painter.setBrush(QBrush(Qt::white));
	painter.drawEllipse(_ballRect);
}

void PongWidget::keyPressEvent(QKeyEvent *event)
{
	int keyCode = event->key();

	switch(keyCode)
	{
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Space:
		{
			this->setLastKeyCode(keyCode);
			break;
		}
		default:
		{
			QWidget::keyPressEvent(event);
			break;
		}
	};
}

void PongWidget::keyReleaseEvent(QKeyEvent *event)
{
	int keyCode = event->key();

	switch(keyCode)
	{
		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Space:
		{
			if (keyCode == this->lastKeyCode())
			{
				this->setLastKeyCode(0);
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

/* Returns all shapes to their starting positions and allocates a new AI. */
void PongWidget::reset(QString script)
{
	_script = script;
	QRect rect;
	QRect courtRect = this->rect();

	_court->setRect(courtRect);

	rect = QRect(courtRect.width()/2,10,20,20);
	_ball->setRect(rect);

	rect = QRect(1,50,10,99);
	_leftPaddle->setRect(rect);

	rect = QRect(courtRect.width() - 10,50,10,99);
	_rightPaddle->setRect(rect);

	_deltaX = -kUpdateDistance;
	_deltaY = -kUpdateDistance;

	this->setBallRect(_ball->rect());
	this->setLeftPaddleRect(_leftPaddle->rect());
	this->setRightPaddleRect(_rightPaddle->rect());

	_pongAI = new PongAI(script, this);
}

void PongWidget::update()
{
	int keyCode = this->lastKeyCode();

	// Spacebar
	if (Qt::Key_Space == keyCode)
	{
		this->reset(_script);
		return;
	}

	// Exit off left side of screen
	if (_ball->right() < _court->left())
	{
		this->reset(_script);
		return;
	}

	// Exit off right side of screen
	if (_ball->left() > _court->right())
	{
		this->reset(_script);
		return;
	}

	// Move human paddle
	if (Qt::Key_Up == keyCode)
	{
		if (_leftPaddle->top() > 0)
		{
			_leftPaddle->moveY(-kUpdateDistance);
		}
		this->setLeftPaddleRect(_leftPaddle->rect());
	}
	else if (Qt::Key_Down == keyCode)
	{
		if (_leftPaddle->bottom() < _court->bottom())
		{
			_leftPaddle->moveY(kUpdateDistance);
		}
		this->setLeftPaddleRect(_leftPaddle->rect());
	}

	// Move AI paddle
	Direction direction = _pongAI->nextMove(_rightPaddle, _ball);
	if (direction == kUpDirection)
	{
		if (_rightPaddle->top() > 0)
		{
			_rightPaddle->moveY(-kUpdateDistance);
		}
		this->setRightPaddleRect(_rightPaddle->rect());
	}
	else if (direction == kDownDirection)
	{
		if (_rightPaddle->bottom() < _court->bottom())
		{
			_rightPaddle->moveY(kUpdateDistance);
		}
		this->setRightPaddleRect(_rightPaddle->rect());
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

	this->setBallRect(_ball->rect());
	this->repaint();
}
