cmake_minimum_required(VERSION 3.10)

project(RRS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies/WIN32)

    set(SDL2_DIRECTORY ${DEPENDENCIES_DIR}/SDL2-2.30.10)
    set(SDL2_DIR ${SDL2_DIRECTORY}/cmake)
    configure_file(${SDL2_DIRECTORY}/lib/x64/SDL2.dll SDL2.dll COPYONLY)

    set(PUGIXML_SOURCES ${DEPENDENCIES_DIR}/pugixml-1.14/src)
elseif(UNIX)
    find_package(pugixml REQUIRED)
endif()

find_package(SDL2 REQUIRED)

set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(CONFIGS_DIR ${RESOURCES_DIR}/cfg)
set(COUPLINGS_DIR ${CONFIGS_DIR}/couplings)
set(DATA_DIR ${RESOURCES_DIR}/data)
set(DEVICES_DIR ${CONFIGS_DIR}/devices)
set(FONTS_DIR ${RESOURCES_DIR}/fonts)
set(LIBS_DIR ${RESOURCES_DIR}/lib)
set(LOGS_DIR ${RESOURCES_DIR}/logs)
set(MODULES_DIR ${RESOURCES_DIR}/modules)
set(PLUGINS_DIR ${RESOURCES_DIR}/plugins)
set(ROUTES_DIR ${RESOURCES_DIR}/routes)
set(SCREENSHOTS_DIR ${RESOURCES_DIR}/screenshots)
set(SOUNDS_DIR ${DATA_DIR}/sounds)
set(TRAINS_DIR ${CONFIGS_DIR}/trains)
set(VEHICLES_DIR ${CONFIGS_DIR}/vehicles)
set(VEHICLE_MODELS_DIR ${DATA_DIR}/models)
set(VEHICLE_TEXTURES_DIR ${DATA_DIR}/textures)

configure_file(cmake_defines.h.in ${PROJECT_SOURCE_DIR}/include/cmake_defines.h)

set(SIMULATOR_CONSOLE_TYPE_STRING "Simulator (console)")
set(SIMULATOR_GUI_TYPE_STRING "Simulator (with GUI)")
set(VIEWER_NO_GUI_TYPE_STRING "Viewer (no GUI)")
set(VIEWER_GUI_TYPE_STRING "Viewer (with GUI)")
set(SIMULATOR_VIEWER_GUI_TYPE_STRING "Simulator + Viewer (with GUI)")

set(APPLICATION_TYPE ${SIMULATOR_CONSOLE_TYPE_STRING} CACHE STRING "Application type")
set_property(CACHE APPLICATION_TYPE PROPERTY STRINGS
    ${SIMULATOR_CONSOLE_TYPE_STRING}
    ${SIMULATOR_GUI_TYPE_STRING}
    ${VIEWER_NO_GUI_TYPE_STRING}
    ${VIEWER_GUI_TYPE_STRING}
    ${SIMULATOR_VIEWER_GUI_TYPE_STRING}
)

# TODO: Build type conditions
if(APPLICATION_TYPE STREQUAL ${SIMULATOR_CONSOLE_TYPE_STRING})
    # TODO:
elseif(APPLICATION_TYPE STREQUAL ${SIMULATOR_GUI_TYPE_STRING})
    # TODO:
elseif(APPLICATION_TYPE STREQUAL ${VIEWER_NO_GUI_TYPE_STRING})
    # TODO:
elseif(APPLICATION_TYPE STREQUAL ${VIEWER_GUI_TYPE_STRING})
    # TODO:
elseif(APPLICATION_TYPE STREQUAL ${SIMULATOR_VIEWER_GUI_TYPE_STRING})
    # TODO:
endif()

add_executable(RRS
    include/CLI11.hpp
    include/cmake_defines.h
    include/ConfigFile.h
    include/Logger.h
    include/sdl_wrappers/SdlInstance.h
    include/sdl_wrappers/SdlWindowWrapper.h
    include/simulator/Application.h
    include/simulator/CommandLineData.h
    include/simulator/MotionModel.h
    include/simulator/TrainInitializeData.h
    src/ConfigFile.cpp
    src/Logger.cpp
    src/main.cpp
    src/sdl_wrappers/SdlInstance.cpp
    src/sdl_wrappers/SdlWindowWrapper.cpp
    src/simulator/Application.cpp
    src/simulator/MotionModel.cpp
)

target_link_libraries(RRS PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)

target_include_directories(RRS PRIVATE include)

# add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

if(WIN32)
    target_sources(RRS PRIVATE
        ${PUGIXML_SOURCES}/pugiconfig.hpp
        ${PUGIXML_SOURCES}/pugixml.cpp
        ${PUGIXML_SOURCES}/pugixml.hpp
    )

    target_include_directories(RRS PRIVATE ${DEPENDENCIES_DIR}/pugixml-1.14/src)
endif()

if(UNIX)
    target_link_libraries(RRS PRIVATE pugixml::pugixml)
endif()
