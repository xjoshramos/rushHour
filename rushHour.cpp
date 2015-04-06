#include <stdio.h>
#include <assert.h>
#include <opencv2/opencv.hpp>
#include "rushHour.hpp"
using namespace std;



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
	
	for ( int i = secLower; i <= secUpper; i++){
		if (rushHoursArr[i] == 1) continue;
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



        for ( int i = secLower; i <= secUpper; i++){
		if (rushHoursArr[i] == 1) continue;
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
    rushHours.IsRushHour(10800);
    rushHours.IsRushHour(18000);
    
    rushHours.AddTimeSpan(2.00,4.00);
    rushHours.IsRushHour(10800);
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

