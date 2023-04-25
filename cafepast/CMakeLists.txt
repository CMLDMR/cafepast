cmake_minimum_required(VERSION 3.5)

project(cafepast VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")


set(bsoncxx_DIR ../../mongocore/lib/cmake/bsoncxx-3.7.0)
set(mongocxx_DIR ../../mongocore/lib/cmake/mongocxx-3.7.0)

include_directories("${CMAKE_SOURCE_DIR}")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Gui PrintSupport)
#qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} language_en.ts language_mk.ts)
#configure_file(${QM_FILES} ${CMAKE_SOURCE_DIR} COPYONLY)

qt_add_resources(RESOURCES resource.qrc)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE UIFILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cafepast
        MANUAL_FINALIZATION
        ${HEADERS}
        ${SOURCES}
        ${UIFILES}
        ${QM_FILES}
        ${RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cafepast APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cafepast SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cafepast
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cafepast PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::PrintSupport)

target_include_directories(cafepast PUBLIC "../../mongocore/include")
target_link_directories(cafepast PUBLIC "../../mongocore/lib")
target_link_libraries(cafepast PRIVATE MongoCore)


find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

target_link_libraries(cafepast PRIVATE mongo::bsoncxx_shared)
target_link_libraries(cafepast PRIVATE mongo::mongocxx_shared)

set_target_properties(cafepast PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS cafepast
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cafepast)
endif()
