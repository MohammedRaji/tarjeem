##############
## PROJECT SETTING 
#####################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

PROJECT("Tarjeem")
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtSql REQUIRED)
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
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(${QWT_DLL})

SET(MAIN_UI_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tarjeem.cpp
)

SET(MAIN_UI_RC
	${CMAKE_CURRENT_SOURCE_DIR}/resources/tarjeem.qrc
)

SET(MAIN_UI_MOC_HDRS 
	${CMAKE_CURRENT_SOURCE_DIR}/tarjeem.h
)

INCLUDE(${QT_USE_FILE})

QT4_ADD_RESOURCES(MAIN_UI_RC_SRCS ${MAIN_UI_RC})
QT4_WRAP_CPP(MAIN_UI_MOC_SRCS ${MAIN_UI_MOC_HDRS} )

IF(WIN32)
SET(WIN_RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/tarjeem.rc)
ADD_EXECUTABLE(
	${PROJECT_NAME} 
	WIN32
	${MAIN_UI_SOURCES}
	${MAIN_UI_RC_SRCS}
	${MAIN_UI_MOC_SRCS}
	${WIN_RESOURCE_FILE})
ELSE()
ADD_EXECUTABLE(
	${PROJECT_NAME} 
	${MAIN_UI_SOURCES}
	${MAIN_UI_RC_SRCS}
	${MAIN_UI_MOC_SRCS})
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(
	${PROJECT_NAME} 
	${QT_LIBRARIES}
	${QT_QTMAIN_LIBRARY}
)
	
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

IF(UNIX AND NOT APPLE)
    INSTALL(TARGETS ${PROJECT_NAME}
        DESTINATION bin
    )

    FOREACH(LIB QtCore QtXml QtTest QtWebKit QtGui QtNetwork QtScript)
        INSTALL(FILES
            "${QT_LIBRARY_DIR}/lib${LIB}.so.${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}" 
            RENAME "lib${LIB}.so.${QT_VERSION_MAJOR}" 
            DESTINATION bin
        )
    ENDFOREACH(LIB)
ENDIF(UNIX AND NOT APPLE)

IF(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        DESTINATION bin
    )

    INSTALL(FILES
        "${QT_BINARY_DIR}/QtCore${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtSql${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtXml${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtTest${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtWebKit${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtGui${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtNetwork${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtScript${QT_VERSION_MAJOR}.dll" 
        "${QT_BINARY_DIR}/QtSvg${QT_VERSION_MAJOR}.dll" 
        DESTINATION bin
    )
	
    INSTALL(FILES
        "${PROJECT_SOURCE_DIR}/plugins/sqldrivers/qsqlodbc${QT_VERSION_MAJOR}.dll" 
		DESTINATION bin/plugins/sqldrivers
	)
	
ENDIF(WIN32)

INCLUDE(CPack)