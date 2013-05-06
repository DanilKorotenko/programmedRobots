/*************************************************************
* The PongAI class decides the AI's next move by returning
* a Direction from -nextMove. Behind the scenes, it manages
* a JavaScript execution context, and calls a "nextMove"
* function defined in JavaScript in order to decide how to
* move.
************************************************************/

#include "pongai.h"

#include <QDebug>

#include "ProgrammedObjects/ProgrammedObject.h"
#include "ProgrammedObjectPrototype.h"

Q_DECLARE_METATYPE(ProgrammedObject*)

PongAI::PongAI(QString script, QObject *parent) : QObject(parent)
{
	// Set kUpDirection, kDownDirection, and kStationaryDirection global constants.
	_scriptEngine.globalObject().setProperty("kUpDirection", kUpDirection);
	_scriptEngine.globalObject().setProperty("kDownDirection", kDownDirection);
	_scriptEngine.globalObject().setProperty("kStationaryDirection", kStationaryDirection);

	_programmedObjectPrototype = new ProgrammedObjectPrototype(this);
	_scriptEngine.setDefaultPrototype(qMetaTypeId<ProgrammedObject *>(),
		_scriptEngine.newQObject(_programmedObjectPrototype));

	_scriptEngine.evaluate(script);
	_jsNextMoveFunction = _scriptEngine.globalObject().property("nextMove");

}

Direction PongAI::nextMove(ProgrammedObject *paddle, ProgrammedObject *ball)
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
