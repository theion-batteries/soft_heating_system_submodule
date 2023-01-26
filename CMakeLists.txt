############################
###### Cmake template ######
############################

# author: sami dhiab
# email: sami@theion.de



cmake_minimum_required(VERSION 3.5.0)

# project name, exec and lib
set(project_name heating_system)
set(library_name heatingSystemLib)
set(executable_name heatingSystemExe)

project(${project_name} VERSION "1.0")
set(VCPKG_ROOT "C:/vcpkg/installed/x64-windows/share")
set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-windows/share")
#find_package(sockpp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
# set the C++ standard: 20 is set
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_file(heat_config 
        NAMES heat_config.yaml
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/config
        REQUIRED
)
message("found heat config file: ${heat_config}")        
set ( HEAT_CONFIG "${heat_config}" CACHE FILEPATH "${heat_config}")
set(HEAT_CONFIG_DIR ${CMAKE_INSTALL_PREFIX}/config/heat_config.yaml CACHE FILEPATH "${CMAKE_INSTALL_PREFIX}/config/cnt_config.yaml}") 
add_definitions(-DHEAT_CONFIG="${HEAT_CONFIG_DIR}")
# includes
include_directories(${PROJECT_SOURCE_DIR}/includes/
PUBLIC ${SOCKPP_INCLUDE_DIRS}

)
# add all source *.cpp : change repo name
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

# make the exec: change project name
add_executable(${executable_name} ${all_SRCS})
# link againt library
target_link_libraries(${executable_name} 
PUBLIC wsock32 
PUBLIC ws2_32
# sockpp lib
PUBLIC ${SOCKPP_LIBRARIES}
#yaml lib
PUBLIC yaml-cpp
)
add_library(${library_name} 
"${PROJECT_SOURCE_DIR}/src/heating_controller.cpp"
)
target_link_libraries(${library_name} 
PUBLIC wsock32 
PUBLIC ws2_32
# sockpp lib
PUBLIC ${SOCKPP_LIBRARIES}
#yaml lib
PUBLIC yaml-cpp
)
# copy lib/ dlls to exe folder
add_custom_command(TARGET ${executable_name} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${executable_name}> $<TARGET_FILE_DIR:${executable_name}>
  COMMAND_EXPAND_LISTS
  )
# copy dlls one by one 
function(copy_dlls_yaml_target_destination target_exe)
add_custom_command(TARGET ${target_exe} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:yaml-cpp> $<TARGET_FILE_DIR:${target_exe}>
COMMAND_EXPAND_LISTS)
endfunction()

# copy config one by one 
function(copy_cnt_config target_exe config_file)
add_custom_command(TARGET ${target_exe} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy ${config_file} ${HEAT_CONFIG_DIR}  
COMMENT "copy config from ${config_file} to ${HEAT_CONFIG_DIR}"
    )
endfunction()
# install targets: exe dlls in debug config
install(TARGETS ${executable_name} ${library_name}
CONFIGURATIONS Debug
RUNTIME DESTINATION bin/Debug
)



