## Version: $Id$
## 
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change Log:
## 
######################################################################
## 
### Code:

project(dtkDenseVectorTests)

## ###################################################################
## Build tree setup
## ###################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDenseVectorTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkDenseVectorTest.cpp)

## ###################################################################
## Input - introspected
## ###################################################################

create_test_sourcelist(
    ${PROJECT_NAME}_SOURCES_TST
    ${PROJECT_NAME}.cpp
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Build rules
## ###################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Test)

target_link_libraries(${PROJECT_NAME} dtkLinearAlgebraDense)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkDenseVectorTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDenseVectorTest)

######################################################################
### CMakeLists.txt ends here
