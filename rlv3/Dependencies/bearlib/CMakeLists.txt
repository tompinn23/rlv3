add_library(bearlib SHARED IMPORTED GLOBAL)


math(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

if(WIN32)
	if(BITNESS EQUAL "32")
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Windows32/BearLibTerminal.dll")
		set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Windows32/BearLibTerminal.lib")
	else()
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Windows64/BearLibTerminal.dll")
		set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Windows64/BearLibTerminal.lib")
	endif()
elseif(LINUX)
if(BITNESS EQUAL "32")
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Linux32/libBearLibTerminal.so")
	else()
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/Linux64/libBearLibTerminal.so")
	endif()
else()
message(FATAL_ERROR "Unsupported Platform")
endif()

target_include_directories(bearlib INTERFACE ${CMAKE_SOURCE_DIR}/rlv3/Dependencies/bearlib/include)