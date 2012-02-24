/*************************************************************
* The Shape class, a thin wrapper around QRect, is the basic
* model in Pong. We represent both the paddles and the ball
* as Shapes.
************************************************************/

#include "shape.h"

Shape::Shape(QObject *parent) : QObject(parent)
{
}

void Shape::setRect(QRect rect)
{
	_rect.setRect(rect.x(),rect.y(),rect.width(),rect.height());
}

QRect Shape::rect()
{
	return _rect;
}

qint16 Shape::left()
{
	return _rect.left();
}

qint16 Shape::top()
{
	return _rect.top();
}

qint16 Shape::right()
{
	return _rect.right();
}

qint16 Shape::bottom()
{
	return _rect.bottom();
}

qint16 Shape::height()
{
	return _rect.height();
}

qint16 Shape::width()
{
	return _rect.width();
}

qint16 Shape::middleY()
{
	return _rect.center().y();
}

qint16 Shape::middleX()
{
	return _rect.center().x();
}

QRect Shape::leftFaceRect()
{
	QRect result(_rect.left(), _rect.bottom(), 1, _rect.height());
	return result;
}

QRect Shape::rightFaceRect()
{
	QRect result(_rect.right(), _rect.bottom(), 1, _rect.height());
	return result;
}

void Shape::moveX(qint16 deltaX)
{
	_rect.moveLeft(_rect.x() + deltaX);
}

void Shape::moveY(qint16 deltaY)
{
	_rect.moveTop(_rect.y() + deltaY);
}

bool Shape::intersects(QRect rect)
{
	return _rect.intersects(rect);
}
