#include "shapeprototype.h"

#include "shape.h"
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QDebug>

Q_DECLARE_METATYPE(Shape *)

ShapePrototype::ShapePrototype(QObject *parent) : QObject(parent)
{
}

qint16 ShapePrototype::left()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->left();
	}
	return 0;
}

qint16 ShapePrototype::top()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->top();
	}
	return 0;
}

qint16 ShapePrototype::right()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->right();
	}
	return 0;
}

qint16 ShapePrototype::bottom()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->bottom();
	}
	return 0;
}

qint16 ShapePrototype::height()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->height();
	}
	return 0;
}

qint16 ShapePrototype::width()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->width();
	}
	return 0;
}

qint16 ShapePrototype::middleY()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->middleY();
	}
	return 0;
}

qint16 ShapePrototype::middleX()
{
	Shape *scriptShape = qscriptvalue_cast<Shape*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->middleX();
	}
	return 0;
}

QString ShapePrototype::toString()
{
	return QString("Shape:(rect = %0, %1, %2, %3)").arg(left()).arg(right())
		.arg(top()).arg(bottom());
}
