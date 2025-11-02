file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

target_compile_definitions(Engine PRIVATE 
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

set_target_properties(Engine PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/vendor/SDL/include
        ${CMAKE_SOURCE_DIR}/vendor/glm/glm
        ${CMAKE_SOURCE_DIR}/vendor/json/include
)

target_link_libraries(Engine
    PUBLIC
        SDL2
        SDL2main
        SDL2_image
)

if (WIN32)
    add_custom_command(TARGET Engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2>
        $<TARGET_FILE_DIR:Engine>
    )
    add_custom_command(TARGET Engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_image>
        $<TARGET_FILE_DIR:Engine>
    )
endif()
