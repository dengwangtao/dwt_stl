include_directories(${PROJECT_SOURCE_DIR}/DwtSTL)
set(APP_SRC main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stldemo ${APP_SRC})