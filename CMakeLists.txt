cmake_minimum_required(VERSION 3.19)
project(Test_Qt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(Test_Qt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    res.qrc
    Graphics/BulbItem.h
    Graphics/BulbItem.cpp
    Graphics/ComponentItem.h
    Graphics/ComponentItem.cpp
    Graphics/BatteryItem.h
    Graphics/BatteryItem.cpp
    Graphics/ResistorItem.h
    Graphics/ResistorItem.cpp
    Graphics/SwitchItem.h
    Graphics/SwitchItem.cpp

    Graphics/VoltmeterItem.h
    Graphics/VoltmeterItem.cpp
    Graphics/AmmeterItem.cpp
    Graphics/AmmeterItem.cpp
    circuitscene.h circuitscene.cpp

)

target_link_libraries(Test_Qt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Test_Qt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Test_Qt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
