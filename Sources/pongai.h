#ifndef PONGAI_H
#define PONGAI_H

#include <QObject>
#include <QScriptEngine>
#include <QScriptValue>
#include <QString>

class Shape;
class ShapePrototype;

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

	Direction nextMove(Shape *paddle, Shape *ball);

private:
	QScriptEngine _scriptEngine;

	QScriptValue _jsNextMoveFunction;

	ShapePrototype *_shapePrototype;

};

#endif // PONGAI_H
