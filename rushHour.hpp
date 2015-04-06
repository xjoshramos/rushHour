#include <stdio.h>
#include <assert.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;


class TrackRushHour {

        static const int secsInDay = 86400;
        static const int secsInHr  = 60*60;
        static const int secsInMin = 60;
        static const int minsInHr  = 60;
        public:
                TrackRushHour();
                void Init();
                bool IsRushHour(double time);
                bool IsRushHour(int time);
                void AddTimeSpan(int timeLower, int timeUpper);
                void AddTimeSpan(double timeLower, double timeUpper);
        private:
                bool *rushHoursArr = new bool[secsInDay];
                int convertToSec(double time);


};
