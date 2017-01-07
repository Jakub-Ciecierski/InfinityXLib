cmake_minimum_required(VERSION 3.3)

add_subdirectory(configuration)
add_subdirectory(modules)

if (${IFX_BUILD_UNITTESTS})
    add_subdirectory(tests)
endif()

