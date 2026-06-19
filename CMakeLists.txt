cmake_minimum_required(VERSION 3.19)
project(Simple_Circuit_Generator_System LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(Simple_Circuit_Generator_System
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    res.qrc

    Application/ComponentAddController.cpp
    Application/ComponentAddController.h

    Circuit_code/Ammeter.cpp
    Circuit_code/Ammeter.h
    Circuit_code/Battery.cpp
    Circuit_code/Battery.h
    Circuit_code/Bulb.cpp
    Circuit_code/Bulb.h
    Circuit_code/Circuit.cpp
    Circuit_code/Circuit.h
    Circuit_code/CircuitSolver.cpp
    Circuit_code/CircuitSolver.h
    Circuit_code/Component.cpp
    Circuit_code/Component.h
    Circuit_code/connection.cpp
    Circuit_code/connection.h
    Circuit_code/Fixed_resistor.cpp
    Circuit_code/Fixed_resistor.h
    Circuit_code/Node.cpp
    Circuit_code/Node.h
    Circuit_code/Voltmeter.cpp
    Circuit_code/Voltmeter.h
    Circuit_code/Switch.h
    Circuit_code/Switch.cpp

    Graphics/items/AmmeterItem.cpp
    Graphics/items/AmmeterItem.h
    Graphics/items/BatteryItem.cpp
    Graphics/items/BatteryItem.h
    Graphics/items/BulbItem.cpp
    Graphics/items/BulbItem.h
    Graphics/items/ComponentItem.cpp
    Graphics/items/ComponentItem.h
    Graphics/items/ResistorItem.cpp
    Graphics/items/ResistorItem.h
    Graphics/items/SwitchItem.cpp
    Graphics/items/SwitchItem.h
    Graphics/items/VoltmeterItem.cpp
    Graphics/items/VoltmeterItem.h

    Graphics/manager/ComponentItemManager.cpp
    Graphics/manager/ComponentItemManager.h
    Graphics/manager/WireManager.cpp
    Graphics/manager/WireManager.h

    Graphics/scene/circuitscene.cpp
    Graphics/scene/circuitscene.h

    componentpalettewidget.h
    componentpalettewidget.cpp
    componentpalettewidget.ui
)

target_link_libraries(Simple_Circuit_Generator_System
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(Simple_Circuit_Generator_System
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS Simple_Circuit_Generator_System
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Simple_Circuit_Generator_System
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
