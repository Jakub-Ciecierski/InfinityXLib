cmake_minimum_required(VERSION 3.3)

set(APP_NAME "test_ifx")
project(${APP_NAME})

set(INC_DIR include)
set(SRC_DIR src)
set(DEPS_DIR dependencies)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IFX_UNITTESTS_BIN_BUILD_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_definitions(-DGLEW_STATIC)

#---------------------------------
# PHYSX
#---------------------------------

# Set your platform version here (32/64). TODO AUTOMATIC
set(PLATFORM_VERSION 64)

# DEBUG/CHECKED/PROFILE/RELEASE
set(PHYSX_COMPILER_TYPE CHECKED)

# OS
if (MSVC11)
    set(PHYSX_LOCAL_LINK_DIR "vc11win")
endif (MSVC11)
if (MSVC12)
    set(PHYSX_LOCAL_LINK_DIR "vc12win")
endif (MSVC12)
if (MSVC14)
    set(PHYSX_LOCAL_LINK_DIR "vc14win")
endif (MSVC14)
if (UNIX)
    set(PHYSX_LOCAL_LINK_DIR "linux")
endif (UNIX)

# PLATFORM VERSION
IF (PLATFORM_VERSION MATCHES 64)
    set(PHYSX_PLATFORM_VERSION 64)
    set(PHYSX_LOCAL_LINK_DIR "${PHYSX_LOCAL_LINK_DIR}64")
ENDIF ()
IF (PLATFORM_VERSION MATCHES 32)
    IF (WIN32)
        set(PHYSX_PLATFORM_VERSION 86)
        set(PHYSX_LOCAL_LINK_DIR "${PHYSX_LOCAL_LINK_DIR}86")
    ELSE ()
        set(PHYSX_PLATFORM_VERSION 32)
        set(PHYSX_LOCAL_LINK_DIR "${PHYSX_LOCAL_LINK_DIR}32")
    ENDIF ()
ENDIF ()

link_directories(
        "${IFX_ROOT}/${DEPS_DIR}/PhysX-3.4/PhysX_3.4/Lib/${PHYSX_LOCAL_LINK_DIR}"
        "${IFX_ROOT}/${DEPS_DIR}/PhysX-3.4/PhysX_3.4/Bin/${PHYSX_LOCAL_LINK_DIR}")

# LIB - static, BIN - dynamic
set(PHYSX3_EXTENSIONS_LIB
        "PhysX3Extensions${PHYSX_COMPILER_TYPE}")
set(PHYSX3_BIN
        "PhysX3${PHYSX_COMPILER_TYPE}_x${PHYSX_PLATFORM_VERSION}")
set(PHYSX3_COMMON_BIN
        "PhysX3Common${PHYSX_COMPILER_TYPE}_x${PHYSX_PLATFORM_VERSION}")
set(PX_FOUNDATION_BIN
        "PxFoundation${PHYSX_COMPILER_TYPE}_x${PHYSX_PLATFORM_VERSION}")
set(PX_PVD_SDK_BIN
        "PxPvdSDK${PHYSX_COMPILER_TYPE}_x${PHYSX_PLATFORM_VERSION}")

#---------------------------------
# MACROS
#---------------------------------

MACRO(FIND_INCLUDE_DIR return_list regex)
    FILE(GLOB_RECURSE new_list ${regex})
    SET(dir_list "")
    FOREACH (file_path ${new_list})
        string(REGEX MATCH ^.*/include dir ${file_path})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH ()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS ./include/*.h)
include_directories(${INC_DIR} ${INC_DIR})

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SOURCE_FILES)

add_executable(${APP_NAME} ${SOURCE_FILES} ${SRC_FILES})

#----------------------------------
# EXTERNAL
#----------------------------------

#add_subdirectory(${IFX_ROOT}/${DEPS_DIR} ${IFX_LIB_DEPS_BUILD_DIR})

include_directories(${IFX_ROOT}/${DEPS_DIR}/bullet3/src/)
include_directories(${IFX_ROOT}/${DEPS_DIR}/PhysX-3.4/PhysX_3.4/Include)
include_directories(${IFX_ROOT}/${DEPS_DIR}/PhysX-3.4/PxShared/include)
include_directories(${IFX_ROOT}/${DEPS_DIR}/googletest/${INC_DIR})
include_directories(${IFX_ROOT}/${DEPS_DIR}/glfw-3.1.2/${INC_DIR})
include_directories(${IFX_ROOT}/${DEPS_DIR}/assimp-3.1.1/${INC_DIR})
include_directories(${IFX_ROOT}/${DEPS_DIR}/SOIL/src)
include_directories(${IFX_ROOT}/${DEPS_DIR}/glm/${INC_DIR})
include_directories(${IFX_ROOT}/${DEPS_DIR}/glew-2.0.0/include)
include_directories(${IFX_ROOT}/${DEPS_DIR}/RT-FEM/sources/include)
include_directories(${IFX_ROOT}/${DEPS_DIR}/RT-FEM/external/tetgen1.5.0)
include_directories(${IFX_ROOT}/${DEPS_DIR}/RT-FEM/external/eigen)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#---------------------------------
# IFX LIBS
#---------------------------------

#add_subdirectory(${IFX_ROOT} ${IFX_LIB_BUILD_DIR})

include_directories(${IFX_ROOT}/modules/controls/controls/${INC_DIR})
include_directories(${IFX_ROOT}/modules/graphics/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/resources/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/math/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/common/${INC_DIR})
include_directories(${IFX_ROOT}/modules/game/game/${INC_DIR})
include_directories(${IFX_ROOT}/modules/physics/${INC_DIR})
include_directories(${IFX_ROOT}/modules/gui/gui/${INC_DIR})
include_directories(${IFX_ROOT}/modules/gui/editor/${INC_DIR})

#---------------------------------
# LINK
#---------------------------------

target_link_libraries(${APP_NAME}
        game_ifx graphics_ifx physics_ifx math_ifx
        resources_ifx controls_ifx
        common_ifx gui_ifx editor_ifx
        BulletDynamics BulletCollision)

target_link_libraries(${APP_NAME}
        ${PHYSX3_EXTENSIONS_LIB}
        ${PHYSX3_BIN}
        ${PHYSX3_COMMON_BIN}
        ${PX_FOUNDATION_BIN}
        ${PX_PVD_SDK_BIN})

target_link_libraries(${APP_NAME} gtest gtest_main)
target_link_libraries(${APP_NAME} SOIL)
target_link_libraries(${APP_NAME} assimp)
target_link_libraries(${APP_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${APP_NAME} glew20)
target_link_libraries(${APP_NAME} rtfem)

target_link_libraries(${APP_NAME} ${Boost_LIBRARIES})