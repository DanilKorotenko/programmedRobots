/*************************************************************
* The ProgrammedObject class, a thin wrapper around QRect, is the basic
* model in Pong. We represent both the paddles and the ball
* as Shapes.
************************************************************/

#include "ProgrammedObject.h"

#include "../pongai.h"

ProgrammedObject::ProgrammedObject(QObject *parent) : QObject(parent)
{
}

void ProgrammedObject::setRect(QRect rect)
{
	_rect.setRect(rect.x(),rect.y(),rect.width(),rect.height());
}

QRect ProgrammedObject::rect()
{
	return _rect;
}

qint16 ProgrammedObject::left()
{
	return _rect.left();
}

qint16 ProgrammedObject::top()
{
	return _rect.top();
}

qint16 ProgrammedObject::right()
{
	return _rect.right();
}

qint16 ProgrammedObject::bottom()
{
	return _rect.bottom();
}

qint16 ProgrammedObject::height()
{
	return _rect.height();
}

qint16 ProgrammedObject::width()
{
	return _rect.width();
}

qint16 ProgrammedObject::middleY()
{
	return _rect.center().y();
}

qint16 ProgrammedObject::middleX()
{
	return _rect.center().x();
}

QRect ProgrammedObject::leftFaceRect()
{
	QRect result(_rect.left(), _rect.bottom(), 1, _rect.height());
	return result;
}

QRect ProgrammedObject::rightFaceRect()
{
	QRect result(_rect.right(), _rect.bottom(), 1, _rect.height());
	return result;
}

void ProgrammedObject::moveX(qint16 deltaX)
{
	_rect.moveLeft(_rect.x() + deltaX);
}

void ProgrammedObject::moveY(qint16 deltaY)
{
	_rect.moveTop(_rect.y() + deltaY);
}

bool ProgrammedObject::intersects(QRect rect)
{
	return _rect.intersects(rect);
}

QString ProgrammedObject::script()
{
	return _script;
}

void ProgrammedObject::setScript(QString script)
{
	_script = script;
}

void ProgrammedObject::reset()
{
	_pongAI = new PongAI(_script, this);
}

void ProgrammedObject::update(ProgrammedObject *ball, QRect gameAreaRect)
{
	// Move AI paddle
	Direction direction = _pongAI->nextMove(this, ball);
	if (direction == kUpDirection)
	{
		if (this->top() > 0)
		{
			this->moveY(-kUpdateDistance);
		}
	}
	else if (direction == kDownDirection)
	{
		if (this->bottom() < gameAreaRect.bottom())
		{
			this->moveY(kUpdateDistance);
		}
	}
}
