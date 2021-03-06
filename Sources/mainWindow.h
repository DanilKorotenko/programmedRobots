#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

class QTimer;
class GameArea;
class QTextEdit;
class QListWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow();

private slots:
	void slotUpdate();
	void slotTextChanged();

protected:
	void resizeEvent(QResizeEvent *event);

private:
	GameArea *_gameArea;
	QTextEdit *_textEdit;
	QListWidget *_objectsList;

	QTimer *_timer;
};

#endif // MAINWINDOW_H
