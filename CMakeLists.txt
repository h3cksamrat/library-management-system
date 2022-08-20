cmake_minimum_required(VERSION 3.3)

set(BUILD_SSL NO CACHE INTERNAL "")
set(BUILD_TESTS NO CACHE INTERNAL "")
set(BUILD_SHARED YES CACHE INTERNAL "")

project(lms)
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

# include(FetchContent)

# FetchContent_Declare(json
#   GIT_REPOSITORY https://github.com/nlohmann/json.git
#   GIT_PROGRESS TRUE
#   GIT_TAG v3.11.2
# )

# FetchContent_MakeAvailable(json)

# FetchContent_Declare(Crow
#   GIT_REPOSITORY https://github.com/ipkn/crow.git
#   GIT_PROGRESS TRUE
#   GIT_TAG v0.1
# )

# FetchContent_MakeAvailable(Crow)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

# Add an executable with the above sources

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
