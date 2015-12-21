CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(IA54)

SET(EXE_NAME "IA54")

SET(EXECUTABLE_OUTPUT bin/${CMAKE_BUILD_TYPE})

#source grouping macro
# MACRO(SOURCE_GROUP_BY_FOLDER target)
  # SET(SOURCE_GROUP_DELIMITER "/")
  # SET(last_dir "")
  # SET(files "")
  # FOREACH(file ${${target}_SRC} ${${target}_HEADERS})
    # file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}/${target}" ${file})
    # GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    # IF (NOT "${dir}" STREQUAL "${last_dir}")
      # IF (files)
        # SOURCE_GROUP("${last_dir}" FILES ${files})
      # ENDIF (files)
      # SET(files "")
    # ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    # SET(files ${files} ${file})
    # SET(last_dir "${dir}")
  # ENDFOREACH(file)
  # IF (files)
    # SOURCE_GROUP("${last_dir}" FILES ${files})
  # ENDIF (files)
# ENDMACRO(SOURCE_GROUP_BY_FOLDER)

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
FILE(GLOB_RECURSE SRCS_PUGI 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/pugixml/*.cpp 
	${IA54_SOURCE_DIR}/src/pugixml/*.hpp)
FILE(GLOB_RECURSE SRCS_MAIN 
	${IA54_SOURCE_DIR}/src 
	main.cpp)
	
FILE(GLOB_RECURSE SRCS_PROBLEMS_BASE 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Problem.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Problem.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS_DRONES
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Drones/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Drones/*.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS_PENDULUM
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Pendulum/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Pendulum/*.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS_POINTER
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Pointer/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Pointer/*.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS_ROCKET 
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_Terrain.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_Terrain.h
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket.h
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_TerrainEditor.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_TerrainEditor.h
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_Trajectory.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/ProblemRocket_Trajectory.h)
FILE(GLOB_RECURSE SRCS_PROBLEMS_ROCKET_ONE
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Rocket/OneEngine/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/OneEngine/*.h )
FILE(GLOB_RECURSE SRCS_PROBLEMS_ROCKET_TWO
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Problems/Rocket/TwoEngines/*.cpp 
	${IA54_SOURCE_DIR}/src/Problems/Rocket/TwoEngines/*.h )


#Grouping everything
source_group(Agents FILES ${SRCS_AGENTS})
source_group(Bodies FILES ${SRCS_BODIES})
source_group(Graphics FILES ${SRCS_GRAPHICS})
source_group(Simulator FILES ${SRCS_SIMULATOR})
source_group(Utilities FILES ${SRCS_UTILITIES})
source_group(World FILES ${SRCS_WORLD})
source_group(Pugi FILES ${SRCS_PUGI})
source_group(Main FILES ${SRCS_MAIN})

#Problems
SET(SOURCE_GROUP_DELIMITER "/")
source_group(Problems FILES ${SRCS_PROBLEMS_BASE})
source_group(Problems/Drones FILES ${SRCS_PROBLEMS_DRONES})
source_group(Problems/Pendulum FILES ${SRCS_PROBLEMS_PENDULUM})
source_group(Problems/Pointer FILES ${SRCS_PROBLEMS_POINTER})
source_group(Problems/Rocket FILES ${SRCS_PROBLEMS_ROCKET})
source_group(Problems/Rocket/OneEngine FILES ${SRCS_PROBLEMS_ROCKET_ONE})
source_group(Problems/Rocket/TwoEngines FILES ${SRCS_PROBLEMS_ROCKET_TWO})



#ADD_EXECUTABLE(${EXE_NAME} ${SRC_SOURCES} ${SRC_HEADER})

ADD_EXECUTABLE(${EXE_NAME} ${SRCS_AGENTS} ${SRCS_BODIES} ${SRCS_GRAPHICS} ${SRCS_SIMULATOR} ${SRCS_UTILITIES} ${SRCS_WORLD} ${SRCS_PUGI} ${SRCS_MAIN} ${SRCS_PROBLEMS} ${SRCS_PROBLEMS_DRONES} ${SRCS_PROBLEMS_PENDULUM} ${SRCS_PROBLEMS_POINTER}  ${SRCS_PROBLEMS_BASE} ${SRCS_PROBLEMS_ROCKET} ${SRCS_PROBLEMS_ROCKET_ONE} ${SRCS_PROBLEMS_ROCKET_TWO})

FIND_FILE(SFML_CMAKE_DIR "cmake/Modules/FindSFML.cmake")
if(SFML_CMAKE_DIR)
	string(REPLACE "FindSFML.cmake" "" SFML_CMAKE_DIR ${SFML_CMAKE_DIR})
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${SFML_CMAKE_DIR}")
endif()
FIND_PACKAGE(SFML COMPONENTS system window graphics audio network REQUIRED)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${EXE_NAME} ${SFML_LIBRARIES})



