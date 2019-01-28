
TEMPLATE = app
TARGET = XPlay
CONFIG += c++11

DESTDIR = $$OUT_PWD/../bin

QT += core multimedia widgets gui
#CONFIG += debug console
DEFINES += QT_MULTIMEDIA_LIB QT_WIDGETS_LIB

INCLUDEPATH += $$PWD/ffmpeg/include \
               $$PWD/SDL2/include \

LIBS += $$PWD/ffmpeg/lib/avcodec.lib \
        $$PWD/ffmpeg/lib/avdevice.lib \
        $$PWD/ffmpeg/lib/avfilter.lib \
        $$PWD/ffmpeg/lib/avformat.lib \
        $$PWD/ffmpeg/lib/avutil.lib \
        $$PWD/ffmpeg/lib/postproc.lib \
        $$PWD/ffmpeg/lib/swresample.lib \
        $$PWD/ffmpeg/lib/swscale.lib \
        $$PWD/SDL2/lib/x86/SDL2.lib \
        $$PWD/SDL2/lib/x86/SDL2_mixer.lib \
#        $$PWD/SDL2/lib/x86/SDL2main.lib


DEPENDPATH += .

include(XPlay.pri)

win32:RC_FILE = XPlay.rc
