#ifndef PONGWIDGET_H
#define PONGWIDGET_H

#include <QWidget>
#include <QRect>

class ProgrammedObject;

class PongWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PongWidget(QWidget *parent = 0);

	void setScript(QString script);
	void reset();
	void update();

private:
	int _lastKeyCode;

	ProgrammedObject *_leftPaddle;
	ProgrammedObject *_rightPaddle;
	ProgrammedObject *_ball;
	ProgrammedObject *_court;

	int _deltaX;
	int _deltaY;

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);
};

#endif // PONGWIDGET_H
