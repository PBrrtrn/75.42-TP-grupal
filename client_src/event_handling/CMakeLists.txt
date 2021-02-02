project(TPGrupal)

add_library(event-handling SHARED
	InputHandler.cpp
	KeyboardState.cpp
	StatusUpdater.cpp
	UpdateQueue.cpp
)

target_sources(event-handling PRIVATE ../enums/UpdateType.h)
