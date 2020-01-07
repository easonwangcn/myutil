cmake_minimum_required(VERSION 3.0.0)

# ------------------------------------------------------------------------
# project
# ------------------------------------------------------------------------
project(myutil)

# ------------------------------------------------------------------------
# source configure
# ------------------------------------------------------------------------
# configure_file(
#     "${PROJECT_SOURCE_DIR}/inc/playa/core/version.h.in"
#     "${PROJECT_SOURCE_DIR}/inc/playa/core/version.h"
#     )

configure_file(
    "${PROJECT_SOURCE_DIR}/docs/conf.py.in"
    "${PROJECT_SOURCE_DIR}/docs/conf.py"
    )

# ------------------------------------------------------------------------
# target
# ------------------------------------------------------------------------
aux_source_directory(src SOURCE_LIST)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# ------------------------------------------------------------------------
# test target
# ------------------------------------------------------------------------

aux_source_directory(test TEST_SOURCE_LIST)
add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_LIST})
add_dependencies(${PROJECT_NAME}_test ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}_test PRIVATE -save-temps)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# aux_source_directory(test TEST_SOURCE_LIST)
# add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_LIST})

# target_include_directories(${PROJECT_NAME}_test PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/inc
# )
# # depending on the framework, you need to link to it
# target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})

# ------------------------------------------------------------------------
# document
# ------------------------------------------------------------------------
add_custom_target(${PROJECT_NAME}_docs ALL
    ${SPHINX_BUILD}
        -q -b html
        "${CMAKE_CURRENT_SOURCE_DIR}/docs"
        "${PROJECT_SOURCE_DIR}/docs/build"
    COMMENT "Building ${PROJECT_NAME} HTML documentation with Sphinx")

# ------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------

# target
install(TARGETS ${PROJECT_NAME}
    DESTINATION ${PROJECT_NAME}/bin
    )

# include files
install(DIRECTORY inc
    DESTINATION ${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.h"
    )

# docs
install(DIRECTORY docs/build/ 
    DESTINATION ${PROJECT_NAME}/docs
    PATTERN "_sources" EXCLUDE
    PATTERN ".*" EXCLUDE
    )

# ------------------------------------------------------------------------
# clean
# ------------------------------------------------------------------------

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/api"
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/build"
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyoutput"
    )
