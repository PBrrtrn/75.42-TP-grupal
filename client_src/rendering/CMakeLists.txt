project(TPGrupal)

add_library(rendering SHARED
	Animation.cpp
	TimedAnimation.cpp
	Font.cpp
	MapDrawer.cpp
	MusicTrack.cpp
	SoundEffect.cpp
	Renderer.cpp
	MenuRenderer.cpp
	StatisticsRenderer.cpp
	UIDrawer.cpp
	PlayerWeapon.cpp
	Texture.cpp
	Window.cpp
)

target_link_libraries(rendering SDL2 SDL2_image SDL2_ttf SDL2_mixer)