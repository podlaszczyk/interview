set(LIB_NAME DeterminePattern)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} SHARED ${SRC_FILES})
add_library(Model::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME} INTERFACE .)
