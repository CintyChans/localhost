cmake_minimum_required(VERSION 3.24)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
project(test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} /std:c++17")
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

find_package(Protobuf REQUIRED)

if(PROTOBUF_FOUND)
    message ("protobuf found")
else()
    message (FATAL_ERROR "Cannot find Protobuf")
endif()
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS test.proto)
message ("PROTO_SRCS = ${PROTO_SRCS}")
message ("PROTO_HDRS = ${PROTO_HDRS}")
add_executable(main  main.cpp ${PROTO_SRCS} ${PROTO_HDRS} )
add_executable(test_main  test_main.cpp  ${PROTO_SRCS} ${PROTO_HDRS} )
target_include_directories(main PUBLIC ${PROTOBUF_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(main PUBLIC ${PROTOBUF_LIBRARIES})
target_include_directories(test_main PUBLIC ${PROTOBUF_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(test_main PUBLIC ${PROTOBUF_LIBRARIES})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_main PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE Eigen3::Eigen)
target_link_libraries(test_main PRIVATE Eigen3::Eigen)

find_package(argparse CONFIG REQUIRED)
target_link_libraries(main PRIVATE argparse::argparse)
target_link_libraries(test_main PRIVATE argparse::argparse)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt)
target_link_libraries(test_main PRIVATE fmt::fmt)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(test_main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(test_main PRIVATE nlohmann_json::nlohmann_json)

find_package(asio CONFIG REQUIRED)
target_link_libraries(main PRIVATE asio asio::asio)
target_link_libraries(test_main PRIVATE asio asio::asio)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
find_package(eclipse-paho-mqtt-c CONFIG REQUIRED)
target_link_libraries(main PRIVATE eclipse-paho-mqtt-c::paho-mqtt3a eclipse-paho-mqtt-c::paho-mqtt3c eclipse-paho-mqtt-c::paho-mqtt3as eclipse-paho-mqtt-c::paho-mqtt3cs)
target_link_libraries(test_main PRIVATE eclipse-paho-mqtt-c::paho-mqtt3a eclipse-paho-mqtt-c::paho-mqtt3c eclipse-paho-mqtt-c::paho-mqtt3as eclipse-paho-mqtt-c::paho-mqtt3cs)

else()
find_package(eclipse-paho-mqtt-c CONFIG REQUIRED)
target_link_libraries(main PRIVATE eclipse-paho-mqtt-c::paho-mqtt3a-static eclipse-paho-mqtt-c::paho-mqtt3c-static eclipse-paho-mqtt-c::paho-mqtt3as-static eclipse-paho-mqtt-c::paho-mqtt3cs-static)
target_link_libraries(test_main PRIVATE eclipse-paho-mqtt-c::paho-mqtt3a-static eclipse-paho-mqtt-c::paho-mqtt3c-static eclipse-paho-mqtt-c::paho-mqtt3as-static eclipse-paho-mqtt-c::paho-mqtt3cs-static)

endif()
