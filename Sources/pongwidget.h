#ifndef PONGWIDGET_H
#define PONGWIDGET_H

#include <QWidget>
#include <QRect>

class PongWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PongWidget(QWidget *parent = 0);

	QRect leftPaddleRect();
	void setLeftPaddleRect(QRect value);

	QRect rightPaddleRect();
	void setRightPaddleRect(QRect value);

	QRect ballRect();
	void setBallRect(QRect value);

	int lastKeyCode();
	void setLastKeyCode(int keyCode);

private:
	QRect _leftPaddleRect;
	QRect _rightPaddleRect;
	QRect _ballRect;

	int _lastKeyCode;

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

};

#endif // PONGWIDGET_H
