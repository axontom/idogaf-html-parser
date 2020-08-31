cmake_minimum_required(VERSION 3.16)
project(idogaf VERSION 1.0.0 DESCRIPTION "idogaf - c++ html parser")
include(GNUInstallDirs)
set(IDOGAF_SRC_DIR src)
set(IDOGAF_INCLUDE_DIR include)
add_library(idogaf SHARED 
	${IDOGAF_SRC_DIR}/attribute.cpp
	${IDOGAF_SRC_DIR}/class.cpp
	${IDOGAF_SRC_DIR}/document.cpp
	${IDOGAF_SRC_DIR}/element.cpp
	${IDOGAF_SRC_DIR}/id.cpp
	${IDOGAF_SRC_DIR}/misc.cpp
	${IDOGAF_SRC_DIR}/parser.cpp
	${IDOGAF_SRC_DIR}/search.cpp
	${IDOGAF_SRC_DIR}/style.cpp
)
set(IDOGAF_HEADER_FILES
	${IDOGAF_INCLUDE_DIR}/attribute.h
	${IDOGAF_INCLUDE_DIR}/class.h
	${IDOGAF_INCLUDE_DIR}/document.h
	${IDOGAF_INCLUDE_DIR}/element.h
	${IDOGAF_INCLUDE_DIR}/id.h
	${IDOGAF_INCLUDE_DIR}/idogaf.h
	${IDOGAF_INCLUDE_DIR}/misc.h
	${IDOGAF_INCLUDE_DIR}/parser.h
	${IDOGAF_INCLUDE_DIR}/search.h
	${IDOGAF_INCLUDE_DIR}/style.h
)
set (CMAKE_CXX_STANDARD 11)
set_target_properties(idogaf PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)
configure_file(idogaf.pc.in idogaf.pc @ONLY)
target_include_directories(idogaf PUBLIC ${IDOGAF_INCLUDE_DIR})
install(TARGETS idogaf
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES 
    ${IDOGAF_HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/idogaf)
install(FILES ${CMAKE_BINARY_DIR}/idogaf.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
