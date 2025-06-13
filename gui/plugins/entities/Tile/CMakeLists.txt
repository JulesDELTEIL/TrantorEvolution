project(tile)

add_library(${PROJECT_NAME} SHARED
    Tile.cpp
)

add_library(plugin::entity::tile ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    ECS::ECS
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${GUI_HDR_DIR}
        ${PROJECT_SOURCE_DIR}
)