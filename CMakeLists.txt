cmake_minimum_required(VERSION 3.0)

project(kdevmovesplitview
    HOMEPAGE_URL "https://github.com/jonathanpoelen/kdevelop-plugin-move-split-view"
    DESCRIPTION "To switch between the views of KDevelop"
    VERSION 2.0.0
)

find_package(ECM "6.0.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
#include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)


find_package(KF6 REQUIRED COMPONENTS I18n)  # fix for KDevPlatform package
find_package(KDevPlatform 6.0.0 REQUIRED)

#ecm_qt_install_logging_categories(
#    EXPORT kdevmovesplitview
#    FILE movesplitview.categories
#    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
#)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(kdevmovesplitview_SRCS
    movesplitviewplugin.cpp
)

#ecm_qt_declare_logging_category(kdevmovesplitview_SRCS
#    HEADER debug.h
#    IDENTIFIER PLUGIN_ZAZSA
#    CATEGORY_NAME "kdevelop.plugins.movesplitviewplugin"
#    DESCRIPTION "KDevelop plugin: movesplitviewplugin"
#    EXPORT MOVESPLITVIEWPLUGIN
#)

kdevplatform_add_plugin(kdevmovesplitview
    SOURCES ${kdevmovesplitview_SRCS}
)

target_link_libraries(kdevmovesplitview
    KDev::Interfaces
    KDev::Sublime
)
