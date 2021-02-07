project(TPGrupal)

add_library(client-classes SHARED 
	GameLoop.cpp
	ServerConnection.cpp
)

add_subdirectory(event_handling)
add_subdirectory(game_status)
add_subdirectory(rendering)

target_link_libraries(client-classes event-handling game-status rendering)
