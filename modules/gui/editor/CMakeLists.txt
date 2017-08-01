cmake_minimum_required(VERSION 3.3)
set(LIB_NAME "editor_ifx")
project(${LIB_NAME})

set(INC_DIR include)
set(SRC_DIR src)

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


#---------------------------------
# COMPILE FLAGS
#---------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#---------------------------------
# DEPENDENCIES
#---------------------------------

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(${IFX_ROOT}/modules/common/math/${INC_DIR})
include_directories(${IFX_ROOT}/modules/graphics/${INC_DIR})
include_directories(${IFX_ROOT}/modules/object/object/${INC_DIR})
include_directories(${IFX_ROOT}/modules/controls/controls/${INC_DIR})
include_directories(${IFX_ROOT}/modules/gui/gui/${INC_DIR})
include_directories(${IFX_ROOT}/modules/physics/${INC_DIR})
include_directories(${IFX_ROOT}/modules/common/common/${INC_DIR})

include_directories(${IFX_ROOT}/modules/game/game/${INC_DIR})

# MATH
include_directories(${IFX_ROOT}/dependencies/glm/${INC_DIR})

# SHADERS
find_package(OpenGL REQUIRED)
include_directories(${IFX_ROOT}/${DEPS_DIR}/glew-2.0.0/include)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${IFX_ROOT}/modules/common/resources/${INC_DIR})

# MODEL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${IFX_ROOT}/${DEPS_DIR}/glew-2.0.0/include)
include_directories(${IFX_ROOT}/dependencies/SOIL/src)
include_directories(${IFX_ROOT}/modules/graphics/shaders/${INC_DIR})

# OBJECT
include_directories(${IFX_ROOT}/modules/common/math/${INC_DIR})
include_directories(${IFX_ROOT}/${DEPS_DIR}/glm/${INC_DIR})

include_directories(${IFX_ROOT}/${DEPS_DIR}/glfw-3.1.2/${INC_DIR})

#---------------------------------
# PROJECT
#---------------------------------

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS ${INC_DIR}/*.h)
include_directories(${INC_DIR})

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE INC_FILES ${INC_DIR}/*.h)
set(SPAM )

#---------------------------------

if (NOT TARGET ${LIB_NAME})
    add_library(${LIB_NAME} STATIC ${SRC_FILES} ${INC_FILES} ${SPAM})
endif()
set_target_properties(${LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib)