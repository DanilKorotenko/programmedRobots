#include "ProgrammedObjectPrototype.h"

#include "ProgrammedObject.h"
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QDebug>

Q_DECLARE_METATYPE(ProgrammedObject *)

ProgrammedObjectPrototype::ProgrammedObjectPrototype(QObject *parent) : QObject(parent)
{
}

qint16 ProgrammedObjectPrototype::left()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->left();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::top()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->top();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::right()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->right();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::bottom()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->bottom();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::height()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->height();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::width()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->width();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::middleY()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->middleY();
	}
	return 0;
}

qint16 ProgrammedObjectPrototype::middleX()
{
	ProgrammedObject *scriptShape = qscriptvalue_cast<ProgrammedObject*>(thisObject());
	if (scriptShape)
	{
		return scriptShape->middleX();
	}
	return 0;
}

QString ProgrammedObjectPrototype::toString()
{
	return QString("ProgrammedObject:(rect = %0, %1, %2, %3)").arg(left()).arg(right())
		.arg(top()).arg(bottom());
}
