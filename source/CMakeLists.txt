cmake_minimum_required(VERSION 3.26)

project(alloc_prj)

add_executable(alloc 
	main.cpp			
	forward_list.ipp	forward_list.h
	my_allocator.ipp 	my_allocator.h
)

if(MSVC)
		set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT alloc)		
endif ()

target_compile_options(alloc PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX >
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

set_target_properties(alloc PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

