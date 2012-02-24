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

PongWidget::PongWidget(QWidget *parent) : QWidget(parent)
{
	this->setFocusPolicy(Qt::StrongFocus);
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
