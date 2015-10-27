CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(IA54)

SET(EXE_NAME "IA54")

SET(EXECUTABLE_OUTPUT bin/${CMAKE_BUILD_TYPE})

#source grouping macro
MACRO(SOURCE_GROUP_BY_FOLDER target)
  SET(SOURCE_GROUP_DELIMITER "/")
  SET(last_dir "")
  SET(files "")
  FOREACH(file ${${target}_SRC} ${${target}_HEADERS})
    file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}/${target}" ${file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    SET(last_dir "${dir}")
  ENDFOREACH(file)
  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
ENDMACRO(SOURCE_GROUP_BY_FOLDER)

include_directories(${IA54_SOURCE_DIR}/src)


# Finding project files
#FILE (GLOB_RECURSE sourceFiles src/*)
FILE(GLOB_RECURSE SRCS_AGENTS
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Agents/*.cpp 
	${IA54_SOURCE_DIR}/src/Agents/*.h)
FILE(GLOB_RECURSE SRCS_BODIES 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Bodies/*.cpp 
	${IA54_SOURCE_DIR}/src/Bodies/*.h)

FILE(GLOB_RECURSE SRCS_GRAPHICS 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Graphics/*.cpp 
	${IA54_SOURCE_DIR}/src/Graphics/*.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/*.h)
FILE(GLOB_RECURSE SRCS_SIMULATOR 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Simulator/*.cpp 
	${IA54_SOURCE_DIR}/src/Simulator/*.h)
FILE(GLOB_RECURSE SRCS_UTILITIES 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Utilities/*.cpp 
	${IA54_SOURCE_DIR}/src/Utilities/*.h)
FILE(GLOB_RECURSE SRCS_WORLD 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/World/*.cpp 
	${IA54_SOURCE_DIR}/src/World/*.h)
FILE(GLOB_RECURSE SRCS_MAIN 
	${IA54_SOURCE_DIR}/src 
	main.cpp)

source_group(Agents FILES ${SRCS_AGENTS})
source_group(Bodies FILES ${SRCS_BODIES})
source_group(Graphics FILES ${SRCS_GRAPHICS})
source_group(Problems FILES ${SRCS_PROBLEMS})
source_group(Simulator FILES ${SRCS_SIMULATOR})
source_group(Utilities FILES ${SRCS_UTILITIES})
source_group(World FILES ${SRCS_WORLD})
source_group(Main FILES ${SRCS_MAIN})

#ADD_EXECUTABLE(${EXE_NAME} ${SRC_SOURCES} ${SRC_HEADER})

ADD_EXECUTABLE(${EXE_NAME} ${SRCS_AGENTS} ${SRCS_BODIES} ${SRCS_GRAPHICS} ${SRCS_PROBLEMS} ${SRCS_SIMULATOR} ${SRCS_UTILITIES} ${SRCS_WORLD} ${SRCS_MAIN})

FIND_FILE(SFML_CMAKE_DIR "cmake/Modules/FindSFML.cmake")
if(SFML_CMAKE_DIR)
	string(REPLACE "FindSFML.cmake" "" SFML_CMAKE_DIR ${SFML_CMAKE_DIR})
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${SFML_CMAKE_DIR}")
endif()
FIND_PACKAGE(SFML COMPONENTS system window graphics audio network REQUIRED)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${EXE_NAME} ${SFML_LIBRARIES})



