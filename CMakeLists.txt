cmake_minimum_required(VERSION 3.16)

project(contactwork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES contactwork_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        MainWindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(contactwork
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ContactManager.h
        contact.h
        test.json


        views/HomePageView.h
        views/ContactListView.h
        views/ContactEditView.h
        views/ContactDetailView.h
        views/HomePageView.cpp
        views/ContactListView.cpp
        views/ContactDetailView.cpp
        views/ContactEditView.cpp
        views/ContactAddView.h views/ContactAddView.cpp
        include/ElaWidgetTools.qrc
        icon.qrc


        views/BaseView.h views/BaseView.cpp
        views/FavoritePageView.h views/FavoritePageView.cpp
        models/ContactListModel.h models/ContactListModel.cpp
        models/ContactItemDelegate.h models/ContactItemDelegate.cpp
        contact.cpp
        ContactManager.cpp
        AboutPage.h AboutPage.cpp
        SettingsPage.h SettingsPage.cpp
        models/GroupedContactListModel.h models/GroupedContactListModel.cpp
        views/GroupedContactListView.h views/GroupedContactListView.cpp
        models/GroupedContactItemDelegate.h models/GroupedContactItemDelegate.cpp
        models/ContactSignalHub.h models/ContactSignalHub.cpp
        models/FavoriteItemDelegate.h models/FavoriteItemDelegate.cpp

    )



# Define target properties for Android with Qt 6 as:
#    set_property(TARGET contactwork APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(contactwork SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(contactwork
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include_directories(
  include
  ${CMAKE_SOURCE_DIR}
)
include_directories(views)
include_directories(models)

target_link_libraries(contactwork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
${CMAKE_CURRENT_SOURCE_DIR}/lib/libElaWidgetTools.a)
target_link_libraries(contactwork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.contactwork)
endif()
set_target_properties(contactwork PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS contactwork
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(contactwork)
endif()
