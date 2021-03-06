cmake_minimum_required(VERSION 3.5)

project(editor-classes LANGUAGES CXX)

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

#if(ANDROID)
#	add_library(editor-classes SHARED
#    main.cpp
#    mainwindow.cpp
#    mainwindow.h
#    layoutitem.h
#    layoutitem.cpp
#    gamemapgrid.cpp
#    gamemapgrid.h
#    mainwindow.ui
#    WolfEditor.qrc
#  )
#else()
  add_library(editor-classes
    main.cpp
    mainwindow.cpp
    mainwindow.h
    layoutitem.h
    layoutitem.cpp
    gamemapgrid.cpp
    gamemapgrid.h
    #Map.h
    #Map.cpp
    ../../common_src/Map.h
    ../../common_src/Map.cpp
    ../../server_src/games/MapServer.h
    ../../server_src/games/MapServer.cpp
    texture_list.h
    appstatus.cpp
    appstatus.h
    itemdraggable.cpp
    itemdraggable.h
    itemfood.cpp
    itemfood.h
    itemametralladora.cpp
    itemametralladora.h
    itembarrel.cpp
    itembarrel.h
    itemblood.cpp
    itemblood.h
    itembullets.cpp
    itembullets.h
    itemcanion.cpp
    itemcanion.h
    itemspawnpoint.cpp
    itemspawnpoint.h
    object_list.h
    itemkey.cpp
    itemkey.h
    itemmedkit.cpp
    itemmedkit.h
    itemtable.cpp
    itemtable.h
    itemtreasure.cpp
    itemtreasure.h
    itemwater.cpp
    itemwater.h
    newmapwindow.cpp
    newmapwindow.h
    mainwindow.ui
    mapview.cpp
    mapview.h
    editoritemserializer.cpp
    editoritemserializer.h
    ../../common_src/Vector.cpp
    ../../common_src/Vector.h
    ../../server_src/games/SpawnPoint.h
    ../../server_src/games/SpawnPoint.cpp
    ../../server_src/games/SpawnPointSerializer.h
    ../../server_src/games/SpawnPointSerializer.cpp
    ../../server_src/games/player.h
    ../../server_src/games/player.cpp
    ../../server_src/games/door.h
    ../../server_src/games/door.cpp
    ../../server_src/games/DoorSerializer.h
    ../../server_src/games/DoorSerializer.cpp
    ../../server_src/items/arma_ametralladora.cpp
    ../../server_src/items/arma_ametralladora.h
    ../../server_src/items/arma_canion.cpp
    ../../server_src/items/arma_canion.h
    ../../server_src/items/arma_lanzacohetes.cpp
    ../../server_src/items/arma_lanzacohetes.h
    ../../server_src/items/barrel.cpp
    ../../server_src/items/barrel.h
    ../../server_src/items/blood.cpp
    ../../server_src/items/blood.h
    ../../server_src/items/bullets.cpp
    ../../server_src/items/bullets.h
    ../../server_src/items/corpse.cpp
    ../../server_src/items/corpse.h
    ../../server_src/items/food.cpp
    ../../server_src/items/food.h
    ../../server_src/items/item.cpp
    ../../server_src/items/item.h
    ../../server_src/items/ItemSerializer.cpp
    ../../server_src/items/ItemSerializer.h
    ../../server_src/items/key.cpp
    ../../server_src/items/key.h
    ../../server_src/items/medkit.cpp
    ../../server_src/items/medkit.h
    ../../server_src/items/table.cpp
    ../../server_src/items/table.h
    ../../server_src/items/treasure.cpp
    ../../server_src/items/treasure.h
    ../../server_src/items/water.cpp
    ../../server_src/items/water.h
    ../../server_src/weapons/ametralladora.cpp
    ../../server_src/weapons/ametralladora.h
    ../../server_src/weapons/arma.cpp
    ../../server_src/weapons/arma.h
    ../../server_src/weapons/canionDeCadena.cpp
    ../../server_src/weapons/canionDeCadena.h
    ../../server_src/weapons/cuchillo.cpp
    ../../server_src/weapons/cuchillo.h
    ../../server_src/weapons/lanzaCohetes.cpp
    ../../server_src/weapons/lanzaCohetes.h
    ../../server_src/weapons/pistola.cpp
    ../../server_src/weapons/pistola.h
    WolfEditor.qrc
  )
#endif()

target_link_libraries(editor-classes PRIVATE Qt5::Widgets yaml-cpp)
