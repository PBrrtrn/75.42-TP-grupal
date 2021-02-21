cmake_minimum_required(VERSION 3.5)

project(qt-test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(qt-test SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    layoutitem.h
    layoutitem.cpp
    gamemapgrid.cpp
    gamemapgrid.h
    mainwindow.ui
    qt-test.qrc
  )
else()
  add_executable(qt-test
    main.cpp
    mainwindow.cpp
    mainwindow.h
    layoutitem.h
    layoutitem.cpp
    gamemapgrid.cpp
    gamemapgrid.h
    Map.h
    Map.cpp
    texture_list.h
    appstatus.cpp
    appstatus.h
    itemdraggable.cpp
    itemdraggable.h
    itemfood.cpp
    itemfood.h
    newmapwindow.cpp
    newmapwindow.h
    mainwindow.ui
    qt-test.qrc
  )
endif()

target_link_libraries(qt-test PRIVATE Qt5::Widgets yaml-cpp)
