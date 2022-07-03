project(helper)

set(SOURCES src/AStar.cpp src/InfluenceMap.cpp)
set(HEADERS include/AStar.h
            include/Geometry.h
            # include/Point2D.h
            # include/Vect2D.h
            include/InfluenceMap.h
            )

add_library(helper STATIC ${SOURCES} ${HEADERS})
target_include_directories(helper PUBLIC ./include ./src ./templates)