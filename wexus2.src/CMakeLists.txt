
#
# Projects the want to build on hydra should start their CMakeLists.txt with the following:
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#
#FIND_PATH(HYDRA_SRC_PATH CMakeLists.txt DOC "Directory containing the hydra CMakeLists.txt and source code")
#IF(NOT HYDRA_SRC_PATH)
#  MESSAGE(FATAL_ERROR "HYDRA_SRC_PATH must be set")
#ENDIF(NOT HYDRA_SRC_PATH)
#INCLUDE(${HYDRA_SRC_PATH}/CMakeLists.txt)



CMAKE_POLICY(PUSH)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(wexus2)

#we usually want shared so that qt is dynamic
SET(BUILD_SHARED_LIBS "YES" CACHE BOOL "Build shared libraries rather than static ones")

# this is useful is this file is ever INCLUDED by other files
GET_FILENAME_COMPONENT(THIS_PATH ${CMAKE_CURRENT_LIST_FILE} PATH)

IF(BUILD_SHARED_LIBS)
ADD_DEFINITIONS(-DBUILD_SHARED_LIBS)
ENDIF(BUILD_SHARED_LIBS)

#
# Compiler Adjustments
#

IF(UNIX)
ADD_DEFINITIONS(-Wall -Wno-sign-compare)
ENDIF(UNIX)

IF(WIN32)
ADD_DEFINITIONS(/w44018)    # sign compare warning
ADD_DEFINITIONS(/w44018)    # sign compare warning
ADD_DEFINITIONS(/D_CRT_SECURE_NO_WARNINGS)    # disable complaing about ::getenv
ENDIF(WIN32)

#
# QT
#

FIND_PACKAGE(Qt4)
SET(QT_USE_QTXML 1)
SET(QT_DONT_USE_QTGUI 1)    # don't need the GUI (yet)
SET(QT_USE_QTSQL 1)    # for wexus ORM
SET(QT_USE_QTMAIN 1)   # dont forget to add WIN32 to ADD_EXECUTABLE

INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}) #the UI generator puts ui_*.h files here

IF(WIN32 AND BUILD_SHARED_LIBS)
# under windows, libhydra is always static
# its just simpler that way (no need to export symbols, etc)
SET(ALWAYS_WIN32_STATIC STATIC)
ENDIF(WIN32 AND BUILD_SHARED_LIBS)

QT4_WRAP_UI(DESKTOP_UI ${THIS_PATH}/desktop/TagEditorView.ui)
QT4_WRAP_CPP(DESKTOP_MOC ${THIS_PATH}/desktop/FileList.h ${THIS_PATH}/desktop/MainWindow.h ${THIS_PATH}/desktop/VCRView.h
    ${THIS_PATH}/desktop/MainImageView.h ${THIS_PATH}/desktop/InfoView.h
    ${THIS_PATH}/desktop/WideListView.h ${THIS_PATH}/desktop/ListView.h ${THIS_PATH}/desktop/ThumbsView.h
    ${THIS_PATH}/desktop/QueryView.h ${THIS_PATH}/desktop/SearchView.h ${THIS_PATH}/desktop/ShuffleView.h ${THIS_PATH}/desktop/TagSelectView.h
    ${THIS_PATH}/desktop/TagEditorView.h ${THIS_PATH}/desktop/DirView.h)

INCLUDE_DIRECTORIES(${THIS_PATH})

# required for model stuff
#INCLUDE_DIRECTORIES(models)

IF(EXISTS ${THIS_PATH}/blogapp/PostsController/indexHtml.cpp)
ADD_EXECUTABLE(wexusserver
    ${THIS_PATH}/wexus/wexusserver.cpp
    ${THIS_PATH}/wexus/HTTP.cpp ${THIS_PATH}/wexus/HTTPServer.cpp
    ${THIS_PATH}/wexus/HTTPHandlerStack.cpp
    ${THIS_PATH}/wexus/FileHTTPHandler.cpp ${THIS_PATH}/wexus/MimeTypes.cpp
    ${THIS_PATH}/wexus/OpenDatabases.cpp
    ${THIS_PATH}/wexus/Site.cpp ${THIS_PATH}/wexus/Application.cpp ${THIS_PATH}/wexus/Controller.cpp
    ${THIS_PATH}/wexus/HTMLString.cpp ${THIS_PATH}/wexus/ParamsParser.cpp
    ${THIS_PATH}/wexus/Cookies.cpp ${THIS_PATH}/wexus/Context.cpp
    ${THIS_PATH}/wexus/ActiveRecord.cpp ${THIS_PATH}/wexus/ActiveClass.cpp ${THIS_PATH}/wexus/ActiveExpr.cpp
    ${THIS_PATH}/wexus/SessionManager.cpp
    ${THIS_PATH}/wexus/MongooseServer.cpp ${THIS_PATH}/wexus/mongoose.c
    ${THIS_PATH}/wexus/StringUtil.cpp ${THIS_PATH}/wexus/VarPath.cpp
    ${THIS_PATH}/wexus/Widgets.cpp ${THIS_PATH}/wexus/Form.cpp ${THIS_PATH}/wexus/ValidationExpr.cpp
    ${THIS_PATH}/wexus/AssertException.cpp ${THIS_PATH}/wexus/Exception.cpp
    ${THIS_PATH}/wexus/MemberFunction.cpp
    ${THIS_PATH}/wexus/Registry.cpp
    ${THIS_PATH}/wexus/ActiveFile.cpp
    ${THIS_PATH}/wexus/MarkDown.cpp
#helper apps
    ${THIS_PATH}/wexus/RedirectApp.cpp
    ${THIS_PATH}/wexus/FileApp.cpp
    ${THIS_PATH}/wexus/UptimeApp.cpp

#blogapp
    ${THIS_PATH}/blogapp/BlogApp.cpp
    ${THIS_PATH}/blogapp/PostsController.cpp
#models
    ${THIS_PATH}/blogapp/Post.cpp
#views
    ${THIS_PATH}/blogapp/PostsController/indexHtml.cpp
    ${THIS_PATH}/blogapp/PostsController/showHtml.cpp

#wikiapp
    ${THIS_PATH}/wikiapp/WikiApp.cpp
    ${THIS_PATH}/wikiapp/PagesController.cpp
#models
    ${THIS_PATH}/wikiapp/Page.cpp
#views
    ${THIS_PATH}/wikiapp/PagesController/showHtml.cpp
    ${THIS_PATH}/wikiapp/PagesController/editHtml.cpp
    )

TARGET_LINK_LIBRARIES(wexusserver ${QT_LIBRARIES})
IF(NOT SQLITE3_LIBRARY STREQUAL "SQLITE3_LIBRARY-NOTFOUND")
TARGET_LINK_LIBRARIES(wexusserver ${SQLITE3_LIBRARY})
ENDIF(NOT SQLITE3_LIBRARY STREQUAL "SQLITE3_LIBRARY-NOTFOUND")

ELSE(EXISTS ${THIS_PATH}/blogapp/PostsController/indexHtml.cpp)
  MESSAGE(STATUS "NOT building wexusserver - run wexusmake to generate required cpp files")
ENDIF(EXISTS ${THIS_PATH}/blogapp/PostsController/indexHtml.cpp)

ADD_EXECUTABLE(wexusmake
    ${THIS_PATH}/wexus/wexusmake.cpp
    ${THIS_PATH}/wexus/TemplateToken.cpp ${THIS_PATH}/wexus/TemplateTokenList.cpp
    ${THIS_PATH}/wexus/TemplateParser.cpp ${THIS_PATH}/wexus/HTMLTemplateParser.cpp
    ${THIS_PATH}/wexus/ModelToken.cpp
    ${THIS_PATH}/wexus/HeaderModelParser.cpp
    ${THIS_PATH}/wexus/CPPScanner.cpp
    ${THIS_PATH}/wexus/StringUtil.cpp
    ${THIS_PATH}/wexus/HTMLString.cpp
    ${THIS_PATH}/wexus/Exception.cpp
    )

TARGET_LINK_LIBRARIES(wexusmake ${QT_LIBRARIES})
IF(NOT SQLITE3_LIBRARY STREQUAL "SQLITE3_LIBRARY-NOTFOUND")
TARGET_LINK_LIBRARIES(wexusmake ${SQLITE3_LIBRARY})
ENDIF(NOT SQLITE3_LIBRARY STREQUAL "SQLITE3_LIBRARY-NOTFOUND")

CMAKE_POLICY(POP)

