if(NCINE_BUILD_UNIT_TESTS)
	# Download and unpack googletest at configure time
	configure_file(cmake/ncine_gtest_download.in googletest-download/CMakeLists.txt)

	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
	)
	if(result)
		message(STATUS "CMake step for googletest failed: ${result}")
		set(GTEST_ERROR TRUE)
	endif()

	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
	)
	if(result)
		message(STATUS "Build step for googletest failed: ${result}")
		set(GTEST_ERROR TRUE)
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
		${CMAKE_BINARY_DIR}/googletest-build
		EXCLUDE_FROM_ALL
	)

	# The gtest/gtest_main targets carry header search path
	# dependencies automatically when using CMake 2.8.11 or
	# later. Otherwise we have to add them here ourselves.
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include")
	endif()

	if(NOT GTEST_ERROR)
		enable_testing()
		add_subdirectory(unit_tests)
	endif()
endif()