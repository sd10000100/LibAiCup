#include <iostream>
#include "helper/include/InfluenceMapBuilder.h"
#include "helper/src/InfluenceMapBuilder.cpp"
#include "helper/include/AStar.h"
#include "helper/src/AStar.cpp"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int main(int argc, char* argv[])
{
	InfluenceMap<int> inf = InfluenceMap<int>(8,8,0);
	inf.PutPotential(5, 1, Point2D<int>(7,1));
	inf.PutPotential(7, 1, Point2D<int>(1,7));
	//inf.ShowMap();

	AStar<int> star = AStar<int>();
	auto ddd = star.FindPath(Point2D<int>(0,0),Point2D<int>(7,7),8,8,inf.matr );
	for (int i=0;i<inf.sizeX;i++) {
        for (int j=0;j<inf.sizeY;j++) {
			bool isStep = false;
			for(Point2D<int> p : ddd)
			{
				if(p.x == i && p.y == j)
					isStep = true;
			}
			if(isStep)
            	std::cout<< RED<<inf.matr[i][j]<< RESET<<" ";
			else
			{
				std::cout<< inf.matr[i][j]<< " ";
			}
			
        }
        std::cout<<std::endl;
    }
	return 0;
}