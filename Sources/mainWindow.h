#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

class QTimer;
class PongWidget;
class QTextEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow();

private slots:
	void slotUpdate();
	void slotTabDidChange(int tabIndex);

protected:
	void resizeEvent(QResizeEvent *event);

private:
	PongWidget *_pongWidget;
	QTextEdit *_textEdit;

	QTimer *_timer;
};

#endif // MAINWINDOW_H
