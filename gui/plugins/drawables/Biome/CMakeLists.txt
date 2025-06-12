project(biome)

add_library(${PROJECT_NAME} SHARED
    Biome.cpp
)

add_library(plugin::drawable::biome ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    ECS::ECS
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${GUI_HDR_DIR}
        ${PROJECT_SOURCE_DIR}
)