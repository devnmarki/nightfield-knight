project(LevelEditor)

file(GLOB_RECURSE LEVEL_EDITOR_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(LevelEditor ${LEVEL_EDITOR_SOURCES})

target_compile_definitions(LevelEditor PRIVATE 
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

add_custom_command(TARGET LevelEditor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:LevelEditor>/res"
	COMMENT "Copying resource folder..."
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NightfieldKnight PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(LevelEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor/SDL/include
    ${CMAKE_SOURCE_DIR}/vendor/glm/glm
)

target_link_libraries(LevelEditor
    PRIVATE
        Engine
        SDL2
        SDL2main
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
    add_custom_command(TARGET LevelEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2>
        $<TARGET_FILE_DIR:LevelEditor>
    )
    add_custom_command(TARGET LevelEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_image>
        $<TARGET_FILE_DIR:LevelEditor>
    )
    add_custom_command(TARGET LevelEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_ttf>
        $<TARGET_FILE_DIR:LevelEditor>
    )
endif()