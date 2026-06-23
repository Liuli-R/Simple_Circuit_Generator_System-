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
    app_icon.rc

    Styles/base.qss
    Styles/actions.qss
    Styles/palette.qss
    Styles/dock.qss
    Styles/scrollbar.qss

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

    Widgets/Dialog/circuitsettingsdialog.cpp
    Widgets/Dialog/circuitsettingsdialog.h
    Widgets/Dialog/circuitsettingsdialog.ui
    Widgets/Dialog/guidedialog.cpp
    Widgets/Dialog/guidedialog.h
    Widgets/Dialog/guidedialog.ui

    Widgets/Dock/circuitstatusdock.cpp
    Widgets/Dock/circuitstatusdock.h
    Widgets/Dock/circuitstatusdock.ui

    Widgets/Palette/componentpalettewidget.cpp
    Widgets/Palette/componentpalettewidget.h
    Widgets/Palette/componentpalettewidget.ui

    Widgets/TopBar/topactionwidget.cpp
    Widgets/TopBar/topactionwidget.h
    Widgets/TopBar/topactionwidget.ui

    Circuit_code/CircuitSolveResult.h

    Graphics/layout/circuitlayoutbuilder.h
    Graphics/layout/circuitlayoutbuilder.cpp
    Graphics/layout/ComponentLayout.h
    Graphics/layout/CircuitLayout.h
    Circuit_code/CircuitTopology.cpp
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
