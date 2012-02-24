/*************************************************************
* The PongAI class decides the AI's next move by returning
* a Direction from -nextMove. Behind the scenes, it manages
* a JavaScript execution context, and calls a "nextMove"
* function defined in JavaScript in order to decide how to
* move.
************************************************************/

#include "pongai.h"

#include <QDebug>

#include "shape.h"
#include "shapeprototype.h"

Q_DECLARE_METATYPE(Shape*)

PongAI::PongAI(QString script, QObject *parent) : QObject(parent)
{
	// Set kUpDirection, kDownDirection, and kStationaryDirection global constants.
	_scriptEngine.globalObject().setProperty("kUpDirection", kUpDirection);
	_scriptEngine.globalObject().setProperty("kDownDirection", kDownDirection);
	_scriptEngine.globalObject().setProperty("kStationaryDirection", kStationaryDirection);

	_shapePrototype = new ShapePrototype(this);
	_scriptEngine.setDefaultPrototype(qMetaTypeId<Shape *>(),
		_scriptEngine.newQObject(_shapePrototype));

	_scriptEngine.evaluate(script);
	_jsNextMoveFunction = _scriptEngine.globalObject().property("nextMove");

}

Direction PongAI::nextMove(Shape *paddle, Shape *ball)
{
	// Cache 'paddle' and 'ball' wrapper objects to pass to 'nextMove' function.
	QScriptValue jsBall = _scriptEngine.newQObject(ball);
	_scriptEngine.globalObject().setProperty("ball", jsBall);

	QScriptValue jsPaddle = _scriptEngine.newQObject(paddle);
	_scriptEngine.globalObject().setProperty("paddle", jsPaddle);

	QScriptValue scriptResult = _jsNextMoveFunction.call(QScriptValue(),
		QScriptValueList() << jsPaddle << jsBall);

	if (_scriptEngine.hasUncaughtException())
	{
		 int lineNo = _scriptEngine.uncaughtExceptionLineNumber();
		 qWarning() << "line: " << lineNo << " : " << scriptResult.toString();
	}

	return (Direction)scriptResult.toNumber();
}
