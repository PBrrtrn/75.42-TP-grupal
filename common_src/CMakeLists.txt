project(TPGrupal)

add_library(common-classes SHARED
	Socket.cpp
	blocking_queue.h
	File.cpp
	Map.cpp
	RayCaster.cpp
	Vector.cpp
	Thread.cpp
	GameListItem.h
)
