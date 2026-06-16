include("E:/Qt_code/Test_Qt/build/Desktop_Qt_6_11_1_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Test_Qt-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "E:/Qt_code/Test_Qt/build/Desktop_Qt_6_11_1_MinGW_64_bit-Debug/Test_Qt.exe"
    GENERATE_QT_CONF
)
