project(TPGrupal)

add_library(event-handling SHARED
	InputHandler.cpp
	MenuInputHandler.cpp
	GameInputHandler.cpp
	KeyboardState.cpp
	StatusUpdater.cpp
	GameStatusUpdater.cpp
	MenuStatusUpdater.cpp
	UpdateQueue.cpp
)

target_sources(event-handling PRIVATE ../enums/UpdateType.h)
target_link_libraries(event-handling SDL2_mixer)
