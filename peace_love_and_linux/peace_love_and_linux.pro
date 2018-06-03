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
    SFM/featureMatcher/BundleAdjuster.cpp \
    SFM/featureMatcher/Visualization.cpp

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
    SFM/featureMatcher/BundleAdjuster.h \
    SFM/featureMatcher/Visualization.h

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
#SSBA
INCLUDEPATH += /opt/git_Atom/SSBA
LIBS += -L/opt/git_Atom/SSBA/build
LIBS +=  /opt/git_Atom/SSBA/build/libV3D.a
LIBS +=  /opt/git_Atom/SSBA/build/libcolamd.a

#boost_system
LIBS += /usr/lib/x86_64-linux-gnu/libboost_system.so.1.58.0
LIBS += /usr/lib/x86_64-linux-gnu/libboost_thread.so

LIBS += -L/usr/lib/x86_64-linux-gnu/ \
        -lboost_system \
        -lboost_thread \

#Eigen3
INCLUDEPATH += /usr/include/eigen3/



#PCL
INCLUDEPATH += /usr/local/pcl-1.8.0/include/pcl-1.8/
LIBS += /usr/local/pcl-1.8.0/lib/libpcl_2d.so \
        /usr/local/pcl-1.8.0/lib/libpcl_common.so \
        /usr/local/pcl-1.8.0/lib/libpcl_features.so \
        /usr/local/pcl-1.8.0/lib/libpcl_filters.so \
        /usr/local/pcl-1.8.0/lib/libpcl_io_ply.so \
        /usr/local/pcl-1.8.0/lib/libpcl_io.so \
        /usr/local/pcl-1.8.0/lib/libpcl_kdtree.so \
        /usr/local/pcl-1.8.0/lib/libpcl_keypoints.so \
        /usr/local/pcl-1.8.0/lib/libpcl_ml.so \
        /usr/local/pcl-1.8.0/lib/libpcl_octree.so \
        /usr/local/pcl-1.8.0/lib/libpcl_outofcore.so \
        /usr/local/pcl-1.8.0/lib/libpcl_people.so \
        /usr/local/pcl-1.8.0/lib/libpcl_recognition.so \
        /usr/local/pcl-1.8.0/lib/libpcl_registration.so \
        /usr/local/pcl-1.8.0/lib/libpcl_sample_consensus.so \
        /usr/local/pcl-1.8.0/lib/libpcl_search.so \
        /usr/local/pcl-1.8.0/lib/libpcl_segmentation.so \
        /usr/local/pcl-1.8.0/lib/libpcl_stereo.so \
        /usr/local/pcl-1.8.0/lib/libpcl_surface.so \
        /usr/local/pcl-1.8.0/lib/libpcl_tracking.so \
        /usr/local/pcl-1.8.0/lib/libpcl_visualization.so\
        -L/usr/local/pcl-1.8.0/lib   -lpcl_common

VTK
INCLUDEPATH += /usr/local/vtk-6.3.0/include/vtk-6.3
#LIBS += /usr/local/vtk-6.3.0/lib/libvtkalglib.so \
#        /usr/local/vtk-6.3.0/lib/libvtkCharts.so \
#        /usr/local/vtk-6.3.0/lib/libvtkChartsTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkCommon.so \
#        /usr/local/vtk-6.3.0/lib/libvtkCommonTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkDICOMParser.so \
#        /usr/local/vtk-6.3.0/lib/libvtkexoIIc.so \
#        /usr/local/vtk-6.3.0/lib/libvtkFiltering.so \
#        /usr/local/vtk-6.3.0/lib/libvtkFilteringTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkftgl.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGenericFiltering.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGenericFilteringTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGeovis.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGeovisTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGraphics.so \
#        /usr/local/vtk-6.3.0/lib/libvtkGraphicsTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkHybrid.so \
#        /usr/local/vtk-6.3.0/lib/libvtkHybridTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkImaging.so \
#        /usr/local/vtk-6.3.0/lib/libvtkImagingTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkInfovis.so \
#        /usr/local/vtk-6.3.0/lib/libvtkInfovisTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkIO.so \
#        /usr/local/vtk-6.3.0/lib/libvtkIOTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkmetaio.so \
#        /usr/local/vtk-6.3.0/lib/libvtkParallel.so \
#        /usr/local/vtk-6.3.0/lib/libvtkParallelTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkproj4.so \
#        /usr/local/vtk-6.3.0/lib/libvtkQtChart.so.5.10 \
#        /usr/local/vtk-6.3.0/lib/libvtkRendering.so \
#        /usr/local/vtk-6.3.0/lib/libvtkRenderingTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtksys.so \
#        /usr/local/vtk-6.3.0/lib/libvtkverdict.so \
#        /usr/local/vtk-6.3.0/lib/libvtkViews.so \
#        /usr/local/vtk-6.3.0/lib/libvtkViewsTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkVolumeRendering.so \
#        /usr/local/vtk-6.3.0/lib/libvtkVolumeRenderingTCL.so \
#        /usr/local/vtk-6.3.0/lib/libvtkWidgets.so \
#        /usr/local/vtk-6.3.0/lib/libvtkWidgetsTCL.so \



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
