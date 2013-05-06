#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T23:37:08
#
#-------------------------------------------------

QT += widgets script

TARGET = JSPong_Qt
TEMPLATE = app

SOURCES += ./Sources/main.cpp \
	./Sources/pongwidget.cpp \
	./Sources/mainWindow.cpp \
	./Sources/ProgrammedObjects/ProgrammedObject.cpp \
	./Sources/pongai.cpp \
	./Sources/ProgrammedObjectPrototype.cpp

HEADERS  += \
	./Sources/pongwidget.h \
	./Sources/mainWindow.h \
	./Sources/ProgrammedObjects/ProgrammedObject.h \
	./Sources/pongai.h \
	./Sources/ProgrammedObjectPrototype.h

RESOURCES += \
	./Resources/resources.qrc

OTHER_FILES += \
	./Resources/PongAI.js
