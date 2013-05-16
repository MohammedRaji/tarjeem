##############
## PROJECT SETTING 
#####################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

IF(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

PROJECT("Tarjeem")

SET(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.0.2\\5.0.2\\msvc2010\\")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets)

SET(CMAKE_BUILD_TYPE Release)

###############################################
## OUTPUT DIRECTORY SETUP
###############################################
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${PROJECT_BINARY_DIR}/bin
	CACHE PATH
	"Single directory for all libraries"
	)
   
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${PROJECT_BINARY_DIR}/bin
	CACHE PATH
	"Single directory for all executable and dll"
	)

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${PROJECT_BINARY_DIR}/lib
	CACHE PATH
	"Single directory for all static libraries"
	)
	
#####################################################
## CPP COMPILER
#####################################################
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})

ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(MAIN_UI_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tarjeem.cpp
)

SET(MAIN_UI_MOC_HDRS 
	${CMAKE_CURRENT_SOURCE_DIR}/tarjeem.h
)

SET(MAIN_UI_RC ${CMAKE_CURRENT_SOURCE_DIR}/resources/tarjeem.qrc)

QT5_ADD_RESOURCES(MAIN_UI_RC_SRCS ${MAIN_UI_RC})

SET(WIN_RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/tarjeem.rc)
ADD_EXECUTABLE(
	${PROJECT_NAME} 
	WIN32
	${MAIN_UI_SOURCES}
	${MAIN_UI_RC_SRCS}
	${MAIN_UI_MOC_SRCS}
	${WIN_RESOURCE_FILE})

QT5_USE_MODULES(${PROJECT_NAME} Widgets Sql)	
SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE_DEBUG 0)

#####################################################
## PACKAGE 
#####################################################
SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_VENDOR "AirQuest-LTE")
SET(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME};Tarjeem)
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/resources/\\\\installer_header.bmp")
SET(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/resources/\\\\icon.ico")
SET(CPACK_NSIS_MUI_UNIICON "${PROJECT_SOURCE_DIR}/resources/\\\\icon.ico")

SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Tarjeem Desktop 0.1.1")
SET(CPACK_PACKAGE_VERSION "0.1.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

IF(WIN32 AND NOT UNIX)
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\Tarjeem.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}Tarjeem")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.airquest-lte.com")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.airquest-lte.com")
  SET(CPACK_NSIS_CONTACT "info@airquest-lte.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_NSIS_MENU_LINKS "doc/index.html" "Help Center")
ENDIF(WIN32 AND NOT UNIX)

INCLUDE(InstallRequiredSystemLibraries)

IF(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        DESTINATION bin
    )
	
	##THIS IS CURRENTLY HARD CODED
    INSTALL(FILES
        "C:/Qt/Qt5.0.2/5.0.2/msvc2010/bin/Qt5Core.dll" 
        "C:/Qt/Qt5.0.2/5.0.2/msvc2010/bin/Qt5Widgets.dll" 
        "C:/Qt/Qt5.0.2/5.0.2/msvc2010/bin/Qt5Sql.dll" 
        DESTINATION bin
    )
	
    INSTALL(FILES
        "${PROJECT_SOURCE_DIR}/plugins/sqldrivers/qsqlodbc.dll" 
		DESTINATION bin/plugins/sqldrivers
	)

    INSTALL(FILES
        "${PROJECT_SOURCE_DIR}/books/example.bok" 
		DESTINATION bin/books
	)
	
ENDIF(WIN32)

INCLUDE(CPack)