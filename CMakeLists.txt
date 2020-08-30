cmake_minimum_required(VERSION 3.16)
project(idogaf VERSION 1.0.0 DESCRIPTION "idogaf - c++ html parser")
include(GNUInstallDirs)
add_library(idogaf SHARED 
	src/attribute.cpp
	src/class.cpp
	src/document.cpp
	src/element.cpp
	src/id.cpp
	src/misc.cpp
	src/parser.cpp
	src/search.cpp
	src/style.cpp
)
set (CMAKE_CXX_STANDARD 11)
set_target_properties(idogaf PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/idogaf.h)
configure_file(idogaf.pc.in idogaf.pc @ONLY)
target_include_directories(idogaf PUBLIC include)
install(TARGETS idogaf
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/idogaf.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
