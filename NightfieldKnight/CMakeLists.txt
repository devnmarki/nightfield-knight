file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
	COMMENT "Copying resource folder..."
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NightfieldKnight PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor/SDL/include
    ${CMAKE_SOURCE_DIR}/vendor/glm/glm
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Engine
        SDL2
        SDL2main
        box2d
)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_image>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_ttf>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()