#pragma once
#include "functions.h"

void writeStatistic(sStatistic &statistic, frame f, int start, int stop, int simulationTime, SYSTEMTIME st, bool flag);
void ssToFile(sStatistic statistic, int sNum, string mode);
void fifo(int sNum, int simulatiomTime, SYSTEMTIME start, mutex &lm, mutex &m, mutex &rm,
	vector<frame> &slBuffer, vector<frame> &sBuffer, vector<frame> &srBuffer);
void lifo(int sNum, int simulatiomTime, SYSTEMTIME start, mutex &lm, mutex &m, mutex &rm,
	vector<frame> &slBuffer, vector<frame> &sBuffer, vector<frame> &srBuffer);
void relativePrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex &lm, mutex &m, mutex &rm,
	vector<frame> &slBuffer, vector<frame> &sBuffer, vector<frame> &srBuffer);
void absolutePrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex &lm, mutex &m, mutex &rm,
	vector<frame> &slBuffer, vector<frame> &sBuffer, vector<frame> &srBuffer);
void mixedPrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex &lm, mutex &m, mutex &rm,
	vector<frame> &slBuffer, vector<frame> &sBuffer, vector<frame> &srBuffer);