#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>

#include <QRect>

class Shape : public QObject
{
	Q_OBJECT
public:
	explicit Shape(QObject *parent = 0);

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

private:
	QRect _rect;

};

#endif // SHAPE_H
