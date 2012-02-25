/*************************************************************
* The ProgrammedObject class, a thin wrapper around QRect, is the basic
* model in Pong. We represent both the paddles and the ball
* as Shapes.
************************************************************/

#include "ProgrammedObject.h"

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
