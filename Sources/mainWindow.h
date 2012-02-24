#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QResizeEvent>

class Shape;
class QTimer;
class PongWidget;
class QTextEdit;
class PongAI;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow();

	void reset();

private slots:
	void slotUpdate();
	void slotTabDidChange(int tabIndex);

protected:
	void resizeEvent(QResizeEvent *event);

private:
	PongWidget *_pongWidget;
	QTextEdit *_textEdit;

	Shape *_leftPaddle;
	Shape *_rightPaddle;
	Shape *_ball;
	Shape *_court;

	PongAI *_pongAI;

	int _deltaX;
	int _deltaY;

	QTimer *_timer;
};

#endif // MAINWINDOW_H
