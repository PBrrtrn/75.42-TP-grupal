project(TPGrupal)

add_library(common_classes SHARED
	blocking_queue.h
	File.cpp
	Map.cpp
	RayCaster.cpp
	Vector.cpp
	Thread.cpp
)
