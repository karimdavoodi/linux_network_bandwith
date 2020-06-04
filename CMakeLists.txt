cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(net_bandwidth)

add_definitions( 
                 -fdiagnostics-show-location=every-line
                 -fdiagnostics-generate-patch 
                 -DBOOST_LOG_DYN_LINK=1
                 -g
                 )

add_executable(${PROJECT_NAME} main.cpp net_bandwidth.cpp)

# Check Boost
find_package(Boost COMPONENTS system program_options  filesystem REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )

add_custom_target(copy ALL 
    COMMAND cp -f net_bandwidth /opt/sms/bin
    COMMENT "Copy to /opt/sms/bin"
    DEPENDS ${PROJECT_NAME}
    )
