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
    Circuit_code/Ammeter.cpp
    Circuit_code/Ammeter.cpp Circuit_code/Ammeter.h Circuit_code/Battery.cpp Circuit_code/Battery.h Circuit_code/Bulb.cpp Circuit_code/Bulb.h Circuit_code/Circuit.cpp Circuit_code/Circuit.h   Circuit_code/CircuitModel.cpp Circuit_code/CircuitModel.h Circuit_code/CircuitSolver.cpp Circuit_code/CircuitSolver.h Circuit_code/Component.cpp Circuit_code/Component.h Circuit_code/connection.cpp Circuit_code/connection.h Circuit_code/Fixed_resistor.cpp Circuit_code/Fixed_resistor.h Circuit_code/Node.cpp Circuit_code/Node.h  Circuit_code/Voltmeter.cpp Circuit_code/Voltmeter.h

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
