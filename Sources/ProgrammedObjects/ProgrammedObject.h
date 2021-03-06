#ifndef PROGRAMMEDOBJECT_H
#define PROGRAMMEDOBJECT_H

#include <QObject>

#include <QRect>

static int const kUpdateDistance = 4;

class PongAI;

class ProgrammedObject : public QObject
{
	Q_OBJECT
public:
	explicit ProgrammedObject(QObject *parent = 0);

	void setRect(QRect rect);
	QRect rect();

	qint16 left();
	qint16 top();
	qint16 right();
	qint16 bottom();

	qint16 height();
	qint16 width();

	qint16 middleY();
	qint16 middleX();

	QRect leftFaceRect();
	QRect rightFaceRect();

	void moveX(qint16 deltaX);
	void moveY(qint16 deltaY);

	bool intersects(QRect rect);

	QString script();
	void setScript(QString script);

	void reset();
	void update(ProgrammedObject *ball, QRect gameAreaRect);

private:
	QRect _rect;
	QString _script;

	PongAI *_pongAI;
};

#endif // PROGRAMMEDOBJECT_H
