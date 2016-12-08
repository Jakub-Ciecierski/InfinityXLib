cmake_minimum_required(VERSION 3.3)

set(TEST_NAME "test_objects_ifx")
project(${TEST_NAME})

set(INC_DIR include)
set(SRC_DIR src)
set(DEPS_DIR dependencies)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IFX_LIB_UNITTESTS_BUILD_DIR})

#---------------------------------
# MACROS
#---------------------------------

MACRO(FIND_INCLUDE_DIR return_list regex)
    FILE(GLOB_RECURSE new_list ${regex})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        string(REGEX MATCH ^.*/include dir ${file_path})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()


#if (NOT TARGET gtest_main)

#endif()
#add_subdirectory(${IFX_ROOT}/${DEPS_DIR}/googletest
        #${IFX_BUILD_DIR}/InfinityX/dependencies)
#add_subdirectory(${IFX_ROOT}/${DEPS_DIR_NAME}/googletest)


#---------------------------------
# INCLUDES
#---------------------------------

include_directories(${IFX_ROOT}/${DEPS_DIR}/googletest/${INC_DIR})

include_directories(${IFX_ROOT}/modules/graphics/model/${INC_DIR})
include_directories(${IFX_ROOT}/modules/graphics/shaders/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/math/${INC_DIR})
include_directories(${IFX_ROOT}/dependencies/glm/${INC_DIR})

# SHADERS
find_package(OpenGL REQUIRED)
include_directories(${IFX_ROOT}/${DEPS_DIR}/glew-2.0.0/include)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${IFX_ROOT}/modules/common/math/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/resources/${INC_DIR})

# MATH
include_directories(${IFX_ROOT}/dependencies/glm/${INC_DIR})
include_directories(${IFX_ROOT}/dependencies/SOIL/src)

#---------------------------------
# COMPILE FLAGS
#---------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#---------------------------------
# PROJECT
#---------------------------------

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS include/*.h)
include_directories(${INC_DIR})

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SPAM )

add_executable(${TEST_NAME} ${SRC_FILES})

target_link_libraries(${TEST_NAME} gtest gtest_main)
target_link_libraries(${TEST_NAME} ${LIB_NAME} )