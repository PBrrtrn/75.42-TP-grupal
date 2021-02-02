project(TPGrupal)

add_library(rendering SHARED
	Animation.cpp
	MapDrawer.cpp
	Renderer.cpp
	Texture.cpp
	Window.cpp
)

target_link_libraries(rendering SDL2 SDL2_image)