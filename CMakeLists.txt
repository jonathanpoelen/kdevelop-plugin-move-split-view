project(switchviewer)

# set(KDE_MIN_VERSION "4.5.0")
# find_package(KDE4 4.5.0 REQUIRED)
find_package(KDE4 REQUIRED)

include (KDE4Defaults)
include (MacroLibrary)
include (MacroOptionalAddSubdirectory)

# Make sure that we're having RPATH on our installed libs, else using kdevelop
# from prefixes like $HOME/kdevelop breaks
# Code taken from FindKDE4Internal.cmake from KDE 4.5
# list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${LIB_INSTALL_DIR}"
# _isSystemLibDir)
# if("${_isSystemLibDir}" STREQUAL "-1")
# 	set(CMAKE_INSTALL_RPATH "${LIB_INSTALL_DIR}")
# endif("${_isSystemLibDir}" STREQUAL "-1")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# find_package(KDevPlatform 1.2.0 REQUIRED)
find_package(KDevPlatform REQUIRED)

include_directories(${KDEVPLATFORM_INCLUDE_DIR} ${QT_INCLUDE_DIR} ${KDE4_INCLUDES})

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DHAVE_CONFIG_H=1)

########### install target ###############

set(kdevswitchviewer_PART_SRCS switchviewerplugin.cpp)

kde4_add_plugin(kdevswitchviewer ${kdevswitchviewer_PART_SRCS})

target_link_libraries(kdevswitchviewer
	${KDE4_KDECORE_LIBS}
	${KDE4_KDEUI_LIBS}
	${KDE4_KPARTS_LIBS}
	${KDE4_KTEXTEDITOR_LIBS}
	${KDEVPLATFORM_INTERFACES_LIBRARIES}
	${KDEVPLATFORM_SUBLIME_LIBRARIES}
# 	${KDEVPLATFORM_PROJECT_LIBRARIES}
# 	${KDEVPLATFORM_UTIL_LIBRARIES}
# 	${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)


install(TARGETS kdevswitchviewer DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES kdevswitchviewer.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES kdevswitchviewer.rc DESTINATION ${DATA_INSTALL_DIR}/kdevswitchviewer )
