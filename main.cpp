#include <iostream>
#include "InfluenceMap.h"
#include "AStar.h"
#include "Vect2D.h"
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


double MM_PI = 3.14159265358979323846;
int main(int argc, char* argv[])
{
InfluenceMap inf2 = InfluenceMap(8,8,0);
	inf2.putPotentialOnSquare(3, 2, std::make_tuple(3,4));
	//inf2.putPotential(3, 1, std::make_tuple(6,6));
	inf2.putPoint(3,  std::make_tuple(0,4));
	//inf2.putPotential(7, 1, Point2D<int>(1,9));
	auto fff = inf2.getPointWithMinSum(3, std::make_tuple(4,5));
	std::cout<<"fff :" <<get<0>(fff)<< " "<< get<1>(fff)<<std::endl;
	inf2.show();
	
	Vect2D<double> v = Vect2D<double>(std::make_tuple(3,3),std::make_tuple(5,3) );
	std::cout<<"v:"<<v.length()<<std::endl;
	std::cout<<"v-start:"<<get<0>(v.start)<<" "<<get<1>(v.start)<<std::endl;
	std::cout<<"v-finish:"<<get<0>(v.finish)<<" "<<get<1>(v.finish)<<std::endl;

	v.turn(90*MM_PI/180);
std::cout<<"v-start:"<<get<0>(v.start)<<" "<<get<1>(v.start)<<std::endl;
	std::cout<<"v-finish:"<<get<0>(v.finish)<<" "<<get<1>(v.finish)<<std::endl;
	
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
//	return 0;
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
	for (int i=0;i<inf2.sizeX();i++) {
        for (int j=0;j<inf2.sizeY();j++) {
				if(std::get<0>(fff) == i && std::get<1>(fff) == j)
				{	std::cout<< RED<<inf2.field()[i][j]<< RESET<<" ";
			}
			else if(i==4 && j==5)
			{
				std::cout<< GREEN<<inf2.field()[i][j]<< RESET<<" ";
			}
			else
			{
				std::cout<< inf2.field()[i][j]<< " ";
			}
			
        }
        std::cout<<std::endl;
    }
	 return 0;
}