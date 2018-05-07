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
    calibration/operationcalibration.cpp \
    calibration/reprojectioncheck.cpp \
    AR/operationar.cpp \
    SFM/sfmwindow.cpp \
    SFM/common/Common.cpp \
    SFM/featureMatcher/AbstractFeatureMatcher.cpp \
    SFM/featureMatcher/Distance.cpp \
    SFM/featureMatcher/FindCameraMatrices.cpp \
    SFM/featureMatcher/Triangulation.cpp \
    SFM/featureMatcher/cpusurffeaturematcher.cpp \
    SFM/featureMatcher/MultiCameraDistance.cpp \
    common/loadmat.cpp \
    SFM/featureMatcher/MultiCameraPnP.cpp \
    SFM/featureMatcher/SfMUpdateListener.cpp \
    SFM/featureMatcher/BundleAdjuster.cpp

HEADERS  += mainwindow.h \
    calibration/calibrationwindow.h \
    cjson/cJSON.h \
    FONT/iconhelper.h \
    videoCapture/videocapture.h \
    calibration/lookoverimage.h \
    calibration/operationcalibration.h \
    calibration/reprojectioncheck.h \
    AR/operationar.h \
    SFM/sfmwindow.h \
    SFM/common/Common.h \
    SFM/featureMatcher/AbstractFeatureMatcher.h \
    SFM/featureMatcher/IFeatureMatcher.h \
    SFM/featureMatcher/Distance.h \
    SFM/featureMatcher/IDistance.h \
    SFM/featureMatcher/FindCameraMatrices.h \
    SFM/featureMatcher/Triangulation.h \
    SFM/featureMatcher/cpusurffeaturematcher.h \
    SFM/featureMatcher/sfm_config.h \
    SFM/featureMatcher/MultiCameraDistance.h \
    common/loadmat.h \
    SFM/featureMatcher/MultiCameraPnP.h \
    SFM/featureMatcher/SfMUpdateListener.h \
    SFM/featureMatcher/BundleAdjuster.h

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

#xfeatures2d
INCLUDEPATH += /home/atom/下载/opencv_contrib-3.2.0/modules/xfeatures2d/include/opencv2/xfeatures2d \
            /home/atom/下载/opencv_contrib-3.2.0/modules/xfeatures2d/include/opencv2/gpu \
LIBS += -L/home/atom/Download/opencv-3.2.0/build/lib/ \
#        /home/atom/Download/opencv-3.2.0/build/lib/libopencv_xfeatures2d.so
        -lopencv_xfeatures2d




FORMS    += mainwindow.ui \
    calibration/calibrationwindow.ui \
    calibration/lookoverimage.ui \
    calibration/operationcalibration.ui \
    calibration/reprojectioncheck.ui \
    AR/operationar.ui \
    SFM/sfmwindow.ui

RESOURCES += \
    resource.qrc

OTHER_FILES +=

unix:!macx: LIBS += -L$$PWD/../../../../home/atom/Download/opencv-3.2.0/build/lib/ -lopencv_xfeatures2d

INCLUDEPATH += $$PWD/../../../../home/atom/Download/opencv-3.2.0/build/include
DEPENDPATH += $$PWD/../../../../home/atom/Download/opencv-3.2.0/build/include
