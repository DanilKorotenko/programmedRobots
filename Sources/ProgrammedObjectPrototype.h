#ifndef PROGRAMMEDOBJECTPROTOTYPE_H
#define PROGRAMMEDOBJECTPROTOTYPE_H

#include <QObject>
#include <QScriptable>

class ProgrammedObjectPrototype : public QObject, public QScriptable
{
	Q_OBJECT
	Q_PROPERTY(qint16 left READ left)
	Q_PROPERTY(qint16 top READ top)
	Q_PROPERTY(qint16 right READ right)
	Q_PROPERTY(qint16 bottom READ bottom)
	Q_PROPERTY(qint16 height READ height)
	Q_PROPERTY(qint16 width READ width)
	Q_PROPERTY(qint16 middleY READ middleY)
	Q_PROPERTY(qint16 middleX READ middleX)

public:
	ProgrammedObjectPrototype(QObject *parent = 0);

	qint16 left();
	qint16 top();
	qint16 right();
	qint16 bottom();

	qint16 height();
	qint16 width();

	qint16 middleY();
	qint16 middleX();

public slots:
	QString toString();

};

#endif // PROGRAMMEDOBJECTPROTOTYPE_H
