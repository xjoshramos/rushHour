#include <stdio.h>
#include <assert.h>
#include <opencv2/opencv.hpp>

using namespace std;


class TrackRushHour {
	
	static const int secsInDay = 86400;
	static const int secsInHr  = 60*60;
	static const int secsInMin = 60;
	static const int minsInHr  = 60;

	//bool rushHoursArr[ secsInDay ] = {0};
	bool *rushHoursArr = new bool[secsInDay];

	public:
		//const int secsInDay = 86400;

		TrackRushHour();
		void Init();
		bool IsRushHour(double time);
		bool IsRushHour(int time);
		void AddTimeSpan(int timeLower, int timeUpper);
		void AddTimeSpan(double timeLower, double timeUpper);    
	private:
		int convertToSec(double time);



};

int TrackRushHour::convertToSec( double time){
	
	// assert time frame given is correct in time of day
	if (time < 0 || time > 24){
		cout << "ERROR incorrect floating time must be between (0.00,24.00)" << endl;
		assert( time >= 0 && time <= 24);
	
	}


	int sec;
	int hour = floor(time);
	int min  = 100*(abs(hour - time));

	// assert time frame in mins is correct
	if (min >= 60){
		cout << "ERROR incorrect floating time must not have decimal >= 60" << endl;
		assert( min < 60);
	}

	//convert time to seconds
	sec = hour*secsInHr + int(min)*secsInMin;
	
	//cout << " time float = " << time << " , " << " seconds = " << sec << " hours = " << hour << " min = " << min << endl;

	return sec;
};

TrackRushHour::TrackRushHour(){
	
	rushHoursArr[secsInDay] = {0};

}

bool TrackRushHour::IsRushHour( double time ){
	
	int sec = convertToSec(time);
	bool rushHourCheck = rushHoursArr[ sec ];
	
	if (rushHourCheck == 0){
		cout <<"FALSE"<<endl;
		return false;
	}else{
		cout <<"TRUE"<<endl;
		return true;
	}
	
};

bool TrackRushHour::IsRushHour( int sec ){

        bool rushHourCheck = rushHoursArr[ sec ];

        if (rushHourCheck == 0){
                cout <<"FALSE"<<endl;
                return false;
        }else{
                cout <<"TRUE"<<endl;
                return true;
        }

};


void TrackRushHour::AddTimeSpan( double timeLower, double timeUpper ){
	if ( timeLower > timeUpper){
                cout << "ERROR incorrect time span must first argument must be lower than second" << endl;
                assert( timeLower <= timeUpper );
        }	

	if (timeLower < 0 || timeLower > 24 || timeUpper < 0 || timeUpper > 24){
                cout << "ERROR incorrect floating time must be between (0.00,24.00)" << endl;
                assert( timeLower >= 0 && timeLower <= 24 && timeUpper <= 24 && timeUpper >= 0);
                
        }
	

	int secLower = convertToSec(timeLower); 
	int secUpper = convertToSec(timeUpper);
	if( secLower == secUpper ){
		rushHoursArr[secLower] = true;
	}
	
	for ( int i = secLower; i <= secUpper; i++){

		rushHoursArr[i] = true;
	}

};


void TrackRushHour::AddTimeSpan( int secLower, int secUpper ){
        if ( secLower > secUpper){
                cout << "ERROR incorrect time span must first argument must be lower than second" << endl;
                assert( secLower <= secUpper );
        }

        if (secLower < 0 || secLower > secsInDay || secUpper < 0 || secUpper > secsInDay){
                cout << "ERROR incorrect floating time must be between (0.00,24.00)" << endl;
                assert( secLower >= 0 && secLower <= secsInDay && secUpper <= secsInDay && secUpper >= 0);

        }


        if( secLower == secUpper ){
                rushHoursArr[secLower] = true;
        }

        for ( int i = secLower; i <= secUpper; i++){

                rushHoursArr[i] = true;
        }

};

void TrackRushHour::Init(){

	rushHoursArr[secsInDay] = { 0 };	
};


int main(int argc, char** argv )
{
    TrackRushHour rushHours;
    rushHours.Init();
    rushHours.IsRushHour(3.00);
    rushHours.IsRushHour(5.00);
    
    rushHours.AddTimeSpan(2.00,4.00);
    rushHours.IsRushHour(3.00);
    rushHours.IsRushHour(5.00);
	
    rushHours.AddTimeSpan(7.00,9.00);
    rushHours.IsRushHour(3.00);
    rushHours.IsRushHour(5.00);
    rushHours.IsRushHour(7.00);
    rushHours.IsRushHour(11.00);
    
    rushHours.AddTimeSpan(8.00,12.00);
    rushHours.IsRushHour(3.00);
    rushHours.IsRushHour(5.00);
    rushHours.IsRushHour(7.00);
    rushHours.IsRushHour(11.00);


    return 0;
}

