#include <iostream>
#include "InfluenceMapBuilder.h"
#include "AStar.h"
#include <ctime>
#include <vector>
#include <tuple>

using namespace pathfind;

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


template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    if(distance(p,q)<n)
        return q;
    //first = std::find_if(p, q, p);
	int j=0;
	if (p != q)
		for(FwdIt i = p; ++i != q; j++)
			if (j==n)
				*p++ = std::move(*i);
	return p;
}



int main(int argc, char* argv[])
{
InfluenceMap inf2 = InfluenceMap(8,8,0);
	inf2.putPotential(3, 1, std::make_tuple(4,4));
	//inf2.putPotential(7, 1, Point2D<int>(1,9));
	inf2.show();
	

	InfluenceMap inf = InfluenceMap(2000,2000,0);
	inf.putPotential(8, 1, std::make_tuple(7,1));
	inf.putPotential(7, 1, std::make_tuple(1,9));
	//inf.show();
	auto dfg = inf.getPointWithMinSum(2, std::make_tuple(7,1));
	auto vvv = distanceSqr(Point2D<int>(7,1),Point2D<int>(1,9));
	AStar star = AStar();
	std::cout<<"startss:"<<std::endl;
	unsigned int start_time =  clock();
	auto ddd = star.findPath(std::make_tuple(0, 0),std::make_tuple(1999,1999),2000,2000,inf.field() );
	unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
	std::cout<<"sec :" <<search_time/1000.0<<std::endl;
	return 0;
	// InfluenceMap<int> inf = InfluenceMap<int>(8,8,0);
	// inf.putPotential(8, 1, Point2D<int>(7,1));
	// inf.putPotential(7, 1, Point2D<int>(1,9));
	// //inf.show();
	// auto dfg = inf.getPointWithMinSum(2, Point2D<int>(7,1));
	// auto vvv = distanceSqr(Point2D<int>(7,1),Point2D<int>(1,9));
	// AStar<int> star = AStar<int>();
	// std::cout<<"startss:"<<std::endl;
	// unsigned int start_time =  clock();
	// auto ddd = star.findPath(std::make_tuple(0, 0),std::make_tuple(7,7),8,8,inf.field() );
	// unsigned int end_time = clock(); // конечное время
    // unsigned int search_time = end_time - start_time; // искомое время
	// std::cout<<"sec :" <<search_time/1000.0<<std::endl;
	// for(auto p : ddd)
	// 		{
	// 			std::cout<<std::get<0>(p)<<" "<<std::get<1>(p)<<std::endl;
	// 		}
	// std::cout<<ddd.size()<<std::endl;
	// for (int i=0;i<inf.sizeX();i++) {
    //     for (int j=0;j<inf.sizeY();j++) {
	// 		bool isStep = false;
	// 		for(auto p : ddd)
	// 		{
	// 			if(std::get<0>(p) == i && std::get<1>(p) == j)
	// 				isStep = true;
	// 		}
	// 		if(isStep)
    //         	std::cout<< RED<<inf.field()[i][j]<< RESET<<" ";
	// 		else
	// 		{
	// 			std::cout<< inf.field()[i][j]<< " ";
	// 		}
			
    //     }
    //     std::cout<<std::endl;
    // }
	// return 0;
}