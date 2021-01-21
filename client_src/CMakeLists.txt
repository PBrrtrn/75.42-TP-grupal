project(TPGrupal)

add_library(client_classes SHARED
	Animation.cpp
	GameLoop.cpp
	GameStatus.cpp
	GameStatusMonitor.cpp
	KeyboardState.cpp
	MapDrawer.cpp
	Renderer.cpp
	ServerListener.cpp
	Texture.cpp
	Window.cpp
)