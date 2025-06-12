project(resource_node)

add_library(${PROJECT_NAME} SHARED
    ResourceNode.cpp
)

add_library(plugin::drawable::resource_node ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    ECS::ECS
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${GUI_HDR_DIR}
        ${PROJECT_SOURCE_DIR}
)