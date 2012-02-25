#ifndef PONGAI_H
#define PONGAI_H

#include <QObject>
#include <QScriptEngine>
#include <QScriptValue>
#include <QString>

class ProgrammedObject;
class ProgrammedObjectPrototype;

typedef enum
{
	kStationaryDirection = 0,
	kUpDirection,
	kDownDirection
} Direction;

class PongAI : public QObject
{
	Q_OBJECT
public:
	explicit PongAI(QString script, QObject *parent = 0);

	Direction nextMove(ProgrammedObject *paddle, ProgrammedObject *ball);

private:
	QScriptEngine _scriptEngine;

	QScriptValue _jsNextMoveFunction;

	ProgrammedObjectPrototype *_programmedObjectPrototype;

};

#endif // PONGAI_H
