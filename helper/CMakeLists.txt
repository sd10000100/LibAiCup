project(helper)

set(SOURCES src/AStar.cpp src/InfluenceMapBuilder.cpp)
set(HEADERS include/AStar.h
            include/Geometry.h
            include/InfluenceMapBuilder.h
            include/Point2D.h
            include/Vect2D.h
            )
include_directories(
     include
)

add_library(helper ${SOURCES} ${HEADERS})
target_include_directories(helper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})