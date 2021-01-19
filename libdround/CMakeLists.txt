add_library (dround
  src/ByteToolkit.c  
  src/callZlib.c  
  src/iochain.c  
  src/libdround.c  
  src/rw.c
)

target_include_directories(dround 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/dr>
  )

target_link_libraries (dround PUBLIC ${ZLIB_dep} m)

target_compile_options(dround
	PRIVATE $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Wno-unused-parameter>
	)

install (TARGETS dround ${thirdparty_export} EXPORT droundConfig
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install (EXPORT droundConfig DESTINATION share/dround/cmake)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dr)
export(TARGETS dround FILE dround.cmake)
