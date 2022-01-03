//**************************************
// Written for Russian Ai Cups with love 
// for horses and pain in the knees
// by sd10000100 on 05.06.2021.
//
// Метод симуляции отжига
//**************************************

// TODO: 

#pragma once

#include <vector>
#include <string>
#include <tuple>

using namespace std;

namespace ai
{
    template<typename T>
    class IAnnealingAction
    {
    public:
        virtual T calcResult();
    };


    template<typename T> // T - tuple<int, int>
    class SimulatedAnnealing{
    public:
        void init(int countItems, vector<T> startPoints,bool writeLog = true);
        void setPoints(int countItems, vector<T> startPoints);
        void updatePath();
        void burn();
        void findOptimalSequence();
        void swapItemsInPoints(int ind1, int ind2);

        bool isTemperatureHigh();

        int getCountItems();
        int getCountBurns();
        double  getTime();
        void resetTemperature();
        string getLog();
        vector<T> getBestWay();
        int getBestWayCoast();
    private:
        const double EPS = 1e-11;
        vector<T> tempPoints_;
        vector<T> startPoints_;
        vector<T> bestPoints_;

        int pathCoast_ = INT_MAX;
        int bestPathCoast_ = INT_MAX ;

        double temperature_ = 100;
        int countItems_ = 10;
        int countBurns_ = 0;
        double time_ = 0;
        string log_ = "";
    };
}

