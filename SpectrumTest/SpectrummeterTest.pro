TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32{
    PC_HOST += WINDOWS
    OMNI_SDK_PATH="C:/Program Files/Ocean Optics/OmniDriver/"       #Aqui se debe indicar el path donde esta instalado el OmniDriver SDK
    JAVA_JDK_PATH="C:/Program Files/Java/jdk1.6.0_45/"              #Aqui se debe indicar el path donde esta instalado el Java JDK
}else{
    error(Proyecto solo configurado para windows con compilador Visual Studio)
}

#Para incluir el QtSerial cuando se hace uso de QT4, en QT 5.1>, no es necesario pues ya viene incliuda
greaterThan(QT_MAJOR_VERSION, 4) {
    message(Qt Version 5)
}else{
    message(Qt Version 4)
    win32-msvc2013{ #Para Visual C++ 2012/3
        QtSerialport_PATH=$$PWD/3rdparty/QtSerialport-QT4           #Aqui se debe indicar el Path
        exists($$QtSerialport_PATH/lib/x64/QtSerialPort.lib){
            message(Found Qtserialport)
        }else{
            error(Indique un Path valido de QtSerialPort)
        }
    }
    win32-msvc2005{ #Para Visual C++ 2005
        QtSerialport_PATH=$$PWD/3rdparty/QtSerialport-QT4V2           #Aqui se debe indicar el Path para QtSerial de QT4 compilado con vs2005
        exists($$QtSerialport_PATH/lib/x64/QtSerialPort.lib){
            message(Found Qtserialport)
        }else{
            error(Indique un Path valido de QtSerialPort)
        }
    }
    INCLUDEPATH+=$$QtSerialport_PATH/include/
    contains(QMAKE_TARGET.arch, x86_64){
        LIBS+=-L$$QtSerialport_PATH/lib/x64/
    }else{
        LIBS+=-L$$QtSerialport_PATH/lib/x86/
    }
    CONFIG(debug, debug|release){
        LIBS+=-lQtSerialPortd
    }
    CONFIG(release, debug|release){
        LIBS+=-lQtSerialPort
    }
}

CONFIG(debug, debug|release){
    contains(PC_HOST, WINDOWS){
        message(S.O. WINDOWS Debug)
        win32-msvc*{ #Para Visual C++
            message(msvc)
            INCLUDEPATH+=$$OMNI_SDK_PATH/include/
            INCLUDEPATH+=$$JAVA_JDK_PATH/include/
            INCLUDEPATH+=$$JAVA_JDK_PATH/include/win32/
            LIBS+=-L$$OMNI_SDK_PATH/OOI_HOME/
            contains(QMAKE_TARGET.arch, x86_64){
                message(QT 64 bits)
                LIBS+=-lcommon64 -lOmniDriver64
            }else{
                message(QT 32 bits)
                LIBS+=-lcommon32 -lOmniDriver32
            }
        }
    }
}

CONFIG(release, debug|release){
    contains(PC_HOST, WINDOWS){
        message(S.O. WINDOWS Release)
        win32-msvc*{ #Para Visual C++ 2012/3
            message(msvc)
            INCLUDEPATH+=$$OMNI_SDK_PATH/include/
            INCLUDEPATH+=$$JAVA_JDK_PATH/include/
            INCLUDEPATH+=$$JAVA_JDK_PATH/include/win32/
            LIBS+=-L$$OMNI_SDK_PATH/OOI_HOME/
            contains(QMAKE_TARGET.arch, x86_64){
                message(QT 64 bits)
                LIBS+=-lcommon64 -lOmniDriver64
            }else{
                message(QT 32 bits)
                LIBS+=-lcommon32 -lOmniDriver32
            }
        }
    }
}


SOURCES += \
    SpectrometerTest/SpectrometerTest.cpp
