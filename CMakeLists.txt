project(OpenRacingTelemetry-Client)
cmake_minimum_required(VERSION 3.6)
include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Gui Widgets SerialPort Network NetworkAuth LinguistTools REQUIRED)

set(LIBRARY_SOURCES

                    "library/common/Config.h"
                    "library/common/Config.cpp"

                    "library/common/Singleton.h"

                    "library/device/api/v1/apiV1.cpp"

                    "library/device/api/v2/apiV2.cpp"

                    "library/device/api/DeviceApi.cpp"
                    "library/device/api/IDeviceApi.h"
                    "library/device/serialport.cpp"

                    "library/model/Place.cpp"
                    "library/model/Place.h"
                    "library/model/Race.cpp"
                    "library/model/Race.h"
                    "library/model/Record.cpp"
                    "library/model/Record.h"


                    "library/network/NetworkClient.cpp"
                    "library/network/NetworkClient.h"

                    "library/network/ServerClient.cpp"
                    "library/network/ServerClient.h"

                    "library/settings/Settings.cpp"
                    "library/settings/Settings.h"

                    "library/weather/METAR.cpp"
                    "library/weather/TAF.cpp"
                    "library/weather/Weather.cpp")

					
set(CLI_SOURCES "cli/main.cpp")

set(GUI_SOURCES "gui/main.cpp"

                "gui/common/QCLickableLabel.cpp"      

                "gui/ui/login/login.cpp"
                "gui/ui/login/login.h"
                "gui/ui/login/login.ui"

                "gui/ui/session/session.cpp"
                "gui/ui/session/session.h"
                "gui/ui/session/session.ui"

                "gui/ui/session_info/session_info.cpp"
                "gui/ui/session_info/session_info.h"
                "gui/ui/session_info/session_info.ui"

                "gui/ui/settings/settings.cpp"
                "gui/ui/settings/settings.ui"
                )

file(GLOB GUI_XLSX_SOURCE "3rdparty/libxlsx/*.cpp")


#XLSX
add_library(libxlsx SHARED "${GUI_XLSX_SOURCE}")
target_link_libraries(libxlsx Qt5::Core Qt5::Gui)
target_include_directories(libxlsx PRIVATE "${Qt5Gui_PRIVATE_INCLUDE_DIRS}")
target_compile_definitions(libxlsx PRIVATE "-DQT_BUILD_XLSX_LIB")

#Library
add_library(libtelemetry SHARED "${LIBRARY_SOURCES}")
target_include_directories(libtelemetry PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(libtelemetry Qt5::Network Qt5::NetworkAuth Qt5::SerialPort)
generate_export_header(libtelemetry EXPORT_FILE_NAME libtelemetry_export.h)

#CLI
add_executable(client-cli "${CLI_SOURCES}")
target_include_directories(client-cli PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(client-cli PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(client-cli libtelemetry)

#GUI
qt5_create_translation(QM_FILES "${GUI_SOURCES}" "gui/ts/client-gui.ts")
add_executable(client-gui WIN32 "${GUI_SOURCES}" "${QM_FILES}")
target_include_directories(client-gui PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(client-gui PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(client-gui Qt5::Widgets)
target_link_libraries(client-gui libtelemetry)
target_link_libraries(client-gui libxlsx)

install(TARGETS libtelemetry DESTINATION .)
install(TARGETS client-cli DESTINATION .)
install(TARGETS client-gui DESTINATION .)
