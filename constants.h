#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <cmath>

using namespace std;

const int ETHERNET_SPEED = 10;
const int IPGBITS = 96;
double const SLOWDOWN_COEF = 100.0; // ����������� ������ � 100 ��� (��-�� ������� �������� ����������)
int const MIN_FRAME_SIZE = 72;
int const MAX_FRAME_SIZE = 1526;

const int PRIO_TRASHOLD_ONE = 557; // �������� ���� ������ ��� ���������� �� 3 ������
const int PRIO_TRASHHOLD_TWO = 1042;

int const SEC_IN_MIN = 60;
int const MILLI_IN_SEC = 1000;

int const TIMESLOT = 7; // ����������� �������� �������� �������

enum class receivers { ONE, TWO, THREE, FOUR, RANDOM };
enum class onOffSwitch { ON, OFF };
enum class globalPrioValues { ONE, TWO, THREE, FOUR, RANDOM };
enum class insidePrioValues { ONE, TWO, THREE, RANDOM };
enum class switchModes { FIFO, LIFO, RELPRIO, ABSPRIO, MIXED}; // ������ ������ ������������ (��������� ������������)

struct transmitter
{
	int intensity; // ������������� � ���������
	int minFrame; // min and max 
	int maxFrame;
	receivers receiver; // ���������� ������� ����������
	onOffSwitch globalPrio; // ��������� ����������� �������� ����/���
	globalPrioValues globalPrioValue;
	onOffSwitch insidePrio; // ���������� ������������� �����������
	insidePrioValues groupOne; // ����� ������� �� 3 ������ �� �� �����
	insidePrioValues groupTwo; // ������: 72 - 557, ������: 558 - 1042
	insidePrioValues groupThree; // ������: 1043 - 1526
};

struct frame
{
	SYSTEMTIME sendTime; // ����� �������� �����
	SYSTEMTIME someTime; // ����� ��������� � �����������
	int length; // ����� � ������
	int receiver; // ����� �� ���������
	int prio; // ���������
};

// ���������� �����������
struct tStatistic
{
	int sendFrames;
	int receiver1;
	int receiver2;
	int receiver3;
	int receiver4;
	int prio1;
	int prio2;
	int prio3;
	int prio4;
	int group1;
	int group2;
	int group3;
	vector<int> frameDistribution;
	vector<int> prio1Distribution;
	vector<int> prio2Distribution;
	vector<int> prio3Distribution;
	vector<int> prio4Distribution;
};

struct sStatistic
{
	int accepted;
	int transfered;
	int returned;
	vector<int> returnedDistr;
	vector<int> Delay; // �������� ��������
	vector<int> prio1Delay;
	vector<int> prio2Delay;
	vector<int> prio3Delay;
	vector<int> prio4Delay;
	vector<int> ProcessingTime; // �������� ���������
	vector<int> prio1PTime;
	vector<int> prio2PTime;
	vector<int> prio3PTime;
	vector<int> prio4PTime;
	vector<int> bufferSize;
	vector<int> frameDistribution;
	vector<int> prio1Distribution;
	vector<int> prio2Distribution;
	vector<int> prio3Distribution;
	vector<int> prio4Distribution;
	int residue;
};