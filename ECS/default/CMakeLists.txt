project(default)

add_library(${PROJECT_NAME} SHARED
    DefaultDrawable.cpp
    DefaultEntity.cpp
)

target_link_libraries(${PROJECT_NAME}
    ECS::ECS
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${ECS_HDR_DIR}
        ${PROJECT_SOURCE_DIR}
)