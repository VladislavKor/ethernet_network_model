#pragma once
#include "constants.h"

bool readParameters(int &simulationTime, transmitter &t1, transmitter &t2, transmitter &t3, 
	transmitter &t4, vector<switchModes> &sModes);
void printTransmitter(transmitter t);
int getMilliSeconds(SYSTEMTIME st);
void writeStatistic(tStatistic &statistic, frame f, int start, int stop, int simulationTime);
void tsToFile(tStatistic statistic, int tNum);
void generator(int tNum, int simulatiomTime, SYSTEMTIME start, transmitter t, mutex &m, vector<frame> &sBuffer);
void showTime(int simulationTime);
int getMin(vector<int> v);
int getMax(vector<int> v);
double getAve(vector<int> v);
