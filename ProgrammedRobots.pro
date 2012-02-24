#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T23:37:08
#
#-------------------------------------------------

QT += core gui script

TARGET = JSPong_Qt
TEMPLATE = app

SOURCES += ./Sources/main.cpp \
	./Sources/pongwidget.cpp \
	./Sources/mainWindow.cpp \
	./Sources/shape.cpp \
	./Sources/pongai.cpp \
	./Sources/shapeprototype.cpp

HEADERS  += \
	./Sources/pongwidget.h \
	./Sources/mainWindow.h \
	./Sources/shape.h \
	./Sources/pongai.h \
	./Sources/shapeprototype.h

RESOURCES += \
	./Resources/resources.qrc

OTHER_FILES += \
	./Resources/PongAI.js
