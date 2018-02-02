#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T19:16:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = peace_love_and_linux
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calibration/calibrationwindow.cpp \
    cjson/cJSON.c \
    FONT/iconhelper.cpp \
    videoCapture/videocapture.cpp \
    calibration/lookoverimage.cpp \
    calibration/operationcalibration.cpp

HEADERS  += mainwindow.h \
    calibration/calibrationwindow.h \
    cjson/cJSON.h \
    FONT/iconhelper.h \
    videoCapture/videocapture.h \
    calibration/lookoverimage.h \
    calibration/operationcalibration.h

LIBS += -L/usr/local/lib \
    /usr/local/lib/libopencv_core.so \
    /usr/local/lib/libopencv_features2d.so \
    /usr/local/lib/libopencv_flann.so \
    /usr/local/lib/libopencv_highgui.so \
    /usr/local/lib/libopencv_imgcodecs.so \
    /usr/local/lib/libopencv_imgproc.so \
    /usr/local/lib/libopencv_ml.so \
    /usr/local/lib/libopencv_objdetect.so \
    /usr/local/lib/libopencv_photo.so \
    /usr/local/lib/libopencv_shape.so \
    /usr/local/lib/libopencv_stitching.so \
    /usr/local/lib/libopencv_superres.so \
    /usr/local/lib/libopencv_videoio.so \
    /usr/local/lib/libopencv_video.so \
    /usr/local/lib/libopencv_videostab.so \
    /usr/local/lib/libopencv_calib3d.so \


FORMS    += mainwindow.ui \
    calibration/calibrationwindow.ui \
    calibration/lookoverimage.ui \
    calibration/operationcalibration.ui

RESOURCES += \
    resource.qrc
