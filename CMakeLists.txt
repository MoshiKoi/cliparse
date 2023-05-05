cmake_minimum_required(VERSION 3.26)
project(CliParse)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
add_subdirectory(tests)

if (CLIPARSE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_library(cliparse INTERFACE)

target_include_directories(cliparse
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

if (CLIPARSE_INSTALL)
    install(
        TARGETS cliparse
        EXPORT cliparseTargets
        INCLUDES DESTINATION include
    )

    install(DIRECTORY include DESTINATION .)

    install(
        EXPORT cliparseTargets
        FILE cliparseTargets.cmake
        NAMESPACE cliparse::
        DESTINATION lib/cmake/cliparse
    )

    include(CMakePackageConfigHelpers)

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cliparseConfig.cmake"
        INSTALL_DESTINATION lib/cmake/cliparse
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cliparseConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cliparseConfigVersion.cmake"
        DESTINATION lib/cmake/cliparse
    )

    set(version 0.0.1)

    set_property(TARGET cliparse PROPERTY VERSION ${version})
    set_property(TARGET cliparse PROPERTY SOVERSION 0)
    set_property(TARGET cliparse PROPERTY INTERFACE_cliparse_MAJOR_VERSION 0)
    set_property(TARGET cliparse APPEND PROPERTY
        COMPATIBLE_INTERFACE_STRING cliparse_MAJOR_VERSION
    )
    
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cliparseConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
    )
endif()