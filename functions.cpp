#include "functions.h"

bool readParameters(int & simulationTime, transmitter & t1, transmitter & t2, transmitter & t3, transmitter & t4, vector<switchModes> & sModes)
{
	string str; 
	transmitter t{};

	// считываем параметры симул€ции из файла 
	ifstream settingsFile("parameters.txt");
	if (!settingsFile)
		return false;

	getline(settingsFile, str);
	simulationTime = stoi(str.substr(0, str.find(' ')));

	getline(settingsFile, str); // пропуск строки

	for (size_t i = 0; i < 4; i++)
	{
		getline(settingsFile, str); // пропуск строки
		getline(settingsFile, str); // интенсивность
		t.intensity = stoi(str.substr(0, str.find('%')));
		getline(settingsFile, str); // минимальна€ длина кадра
		t.minFrame = stoi(str.substr(0, str.find(' ')));
		getline(settingsFile, str); // максимальна€ длина кадра
		t.maxFrame = stoi(str.substr(0, str.find(' ')));
		getline(settingsFile, str); // получатель
		if (str.substr(0, str.find(' ')) == "ONE")
			t.receiver = receivers::ONE;
		if (str.substr(0, str.find(' ')) == "TWO")
			t.receiver = receivers::TWO;
		if (str.substr(0, str.find(' ')) == "THREE")
			t.receiver = receivers::THREE;
		if (str.substr(0, str.find(' ')) == "FOUR")
			t.receiver = receivers::FOUR;
		if (str.substr(0, str.find(' ')) == "RANDOM")
			t.receiver = receivers::RANDOM;
		getline(settingsFile, str); // вкл/выкл приоритета Ћ—
		if (str.substr(0, str.find(' ')) == "ON")
			t.globalPrio = onOffSwitch::ON;
		if (str.substr(0, str.find(' ')) == "OFF")
			t.globalPrio = onOffSwitch::OFF;
		getline(settingsFile, str); // значение проритета
		if (str.substr(0, str.find(' ')) == "ONE")
			t.globalPrioValue = globalPrioValues::ONE;
		if (str.substr(0, str.find(' ')) == "TWO")
			t.globalPrioValue = globalPrioValues::TWO;
		if (str.substr(0, str.find(' ')) == "THREE")
			t.globalPrioValue = globalPrioValues::THREE;
		if (str.substr(0, str.find(' ')) == "FOUR")
			t.globalPrioValue = globalPrioValues::FOUR;
		if (str.substr(0, str.find(' ')) == "RANDOM")
			t.globalPrioValue = globalPrioValues::RANDOM;
		getline(settingsFile, str); // вкл/выкл внутренних приоритетов
		if (str.substr(0, str.find(' ')) == "ON")
			t.insidePrio = onOffSwitch::ON;
		if (str.substr(0, str.find(' ')) == "OFF")
			t.insidePrio = onOffSwitch::OFF;
		getline(settingsFile, str); // приоритет первой группы
		if (str.substr(0, str.find(' ')) == "ONE")
			t.groupOne = insidePrioValues::ONE;
		if (str.substr(0, str.find(' ')) == "TWO")
			t.groupOne = insidePrioValues::TWO;
		if (str.substr(0, str.find(' ')) == "THREE")
			t.groupOne = insidePrioValues::THREE;
		if (str.substr(0, str.find(' ')) == "RANDOM")
			t.groupOne = insidePrioValues::RANDOM;
		getline(settingsFile, str); // приоритет второй группы
		if (str.substr(0, str.find(' ')) == "ONE")
			t.groupTwo = insidePrioValues::ONE;
		if (str.substr(0, str.find(' ')) == "TWO")
			t.groupTwo = insidePrioValues::TWO;
		if (str.substr(0, str.find(' ')) == "THREE")
			t.groupTwo = insidePrioValues::THREE;
		if (str.substr(0, str.find(' ')) == "RANDOM")
			t.groupTwo = insidePrioValues::RANDOM;
		getline(settingsFile, str); // приоритет третей группы
		if (str.substr(0, str.find(' ')) == "ONE")
			t.groupThree = insidePrioValues::ONE;
		if (str.substr(0, str.find(' ')) == "TWO")
			t.groupThree = insidePrioValues::TWO;
		if (str.substr(0, str.find(' ')) == "THREE")
			t.groupThree = insidePrioValues::THREE;
		if (str.substr(0, str.find(' ')) == "RANDOM")
			t.groupThree = insidePrioValues::RANDOM;
		getline(settingsFile, str); // пропуск строки

		if (i == 0)
			t1 = t;
		if (i == 1)
			t2 = t;
		if (i == 2)
			t3 = t;
		if (i == 3)
			t4 = t;
	}

	getline(settingsFile, str); // пропуск строки
	for (size_t i = 0; i < 4; i++)
	{
		getline(settingsFile, str);
		if (str.substr(0, str.find(' ')) == "FIFO")
			sModes.push_back(switchModes::FIFO);
		if (str.substr(0, str.find(' ')) == "LIFO")
			sModes.push_back(switchModes::LIFO);
		if (str.substr(0, str.find(' ')) == "RELPRIO")
			sModes.push_back(switchModes::RELPRIO);
		if (str.substr(0, str.find(' ')) == "ABSPRIO")
			sModes.push_back(switchModes::ABSPRIO);
		if (str.substr(0, str.find(' ')) == "MIXED")
			sModes.push_back(switchModes::MIXED);
	}
	settingsFile.close();
	return true;
}

void printTransmitter(transmitter t)
{
	cout << "Intensity = " << t.intensity << "%" << endl;
	cout << "Min frame = " << t.minFrame << endl;
	cout << "Max frame = " << t.maxFrame << endl;
	cout << "Receiver number = ";
	if (t.receiver == receivers::ONE)
		cout << "ONE" << endl;
	else if (t.receiver == receivers::TWO)
		cout << "TWO" << endl;
	else if (t.receiver == receivers::THREE)
		cout << "THREE" << endl;
	else if (t.receiver == receivers::FOUR)
		cout << "FOUR" << endl;
	else if (t.receiver == receivers::RANDOM)
		cout << "RANDOM" << endl;
	cout << "Segment priority = ";
	if (t.globalPrio == onOffSwitch::ON)
		cout << "ON";
	else if (t.globalPrio == onOffSwitch::OFF)
		cout << "OFF";
	cout << " Value = ";
	if (t.globalPrioValue == globalPrioValues::ONE)
		cout << "ONE" << endl;
	else if (t.globalPrioValue == globalPrioValues::TWO)
		cout << "TWO" << endl;
	else if (t.globalPrioValue == globalPrioValues::THREE)
		cout << "THREE" << endl;
	else if (t.globalPrioValue == globalPrioValues::FOUR)
		cout << "FOUR" << endl;
	cout << "Frames priority = ";
	if (t.insidePrio == onOffSwitch::ON)
		cout << "ON" << endl;
	else if (t.insidePrio == onOffSwitch::OFF)
		cout << "OFF" << endl;
	cout << "Frames [72-" << PRIO_TRASHOLD_ONE << "] = ";
	if (t.groupOne == insidePrioValues::ONE)
		cout << "ONE" << endl;
	else if (t.groupOne == insidePrioValues::TWO)
		cout << "TWO" << endl;
	else if (t.groupOne == insidePrioValues::THREE)
		cout << "THREE" << endl;
	else if (t.groupOne == insidePrioValues::RANDOM)
		cout << "RANDOM" << endl;
	cout << "Frames [" << PRIO_TRASHOLD_ONE + 1 << "-" << PRIO_TRASHHOLD_TWO << "] = ";
	if (t.groupTwo == insidePrioValues::ONE)
		cout << "ONE" << endl;
	else if (t.groupTwo == insidePrioValues::TWO)
		cout << "TWO" << endl;
	else if (t.groupTwo == insidePrioValues::THREE)
		cout << "THREE" << endl;
	else if (t.groupTwo == insidePrioValues::RANDOM)
		cout << "RANDOM" << endl;
	cout << "Frames [" << PRIO_TRASHHOLD_TWO + 1 << "-1526] = ";
	if (t.groupThree == insidePrioValues::ONE)
		cout << "ONE" << endl;
	else if (t.groupThree == insidePrioValues::TWO)
		cout << "TWO" << endl;
	else if (t.groupThree == insidePrioValues::THREE)
		cout << "THREE" << endl;
	else if (t.groupThree == insidePrioValues::RANDOM)
		cout << "RANDOM" << endl;
}

int getMilliSeconds(SYSTEMTIME st)
{
	return (st.wMinute*SEC_IN_MIN + st.wSecond)*MILLI_IN_SEC + st.wMilliseconds;
}

void writeStatistic(tStatistic & statistic, frame f, int start, int stop, int simulationTime)
{
	statistic.sendFrames += 1;

	if (f.receiver == 1)
		statistic.receiver1 += 1;
	if (f.receiver == 2)
		statistic.receiver2 += 1;
	if (f.receiver == 3)
		statistic.receiver3 += 1;
	if (f.receiver == 4)
		statistic.receiver4 += 1;
	if (f.prio == 1)

		statistic.prio1 += 1;
	if (f.prio == 2)
		statistic.prio2 += 1;
	if (f.prio == 3)
		statistic.prio3 += 1;
	if (f.prio == 4)
		statistic.prio4 += 1;

	if (f.length >= 72 and f.length < PRIO_TRASHOLD_ONE)
		statistic.group1 += 1;
	if (f.length >= PRIO_TRASHOLD_ONE and f.length < PRIO_TRASHHOLD_TWO)
		statistic.group2 += 1;
	if (f.length >= PRIO_TRASHHOLD_TWO and f.length <= 1526)
		statistic.group3 += 1;

	int leftBorder = start;
	int rightBorder;
	int sendTime;
	int x = (stop - start) / (10 * simulationTime);
	for (int i = 1; i <= (10 * simulationTime); i++)
	{
		sendTime = getMilliSeconds(f.sendTime);
		rightBorder = leftBorder + x;
		if (sendTime > leftBorder and sendTime <= rightBorder)
		{
			if (statistic.frameDistribution.size() == i)
			{
				statistic.frameDistribution[i - 1] += 1;
				if (f.prio == 1)
					statistic.prio1Distribution[i - 1] += 1;
				if (f.prio == 2)
					statistic.prio2Distribution[i - 1] += 1;
				if (f.prio == 3)
					statistic.prio3Distribution[i - 1] += 1;
				if (f.prio == 4)
					statistic.prio4Distribution[i - 1] += 1;
			}
			else
			{
				statistic.frameDistribution.push_back(1);
				statistic.prio1Distribution.push_back(0);
				statistic.prio2Distribution.push_back(0);
				statistic.prio3Distribution.push_back(0);
				statistic.prio4Distribution.push_back(0);
				if (f.prio == 1)
					statistic.prio1Distribution.back() += 1;
				if (f.prio == 2)
					statistic.prio2Distribution.back() += 1;
				if (f.prio == 3)
					statistic.prio3Distribution.back() += 1;
				if (f.prio == 4)
					statistic.prio4Distribution.back() += 1;
			}

			break;
 		}
		leftBorder += x;
	}
}

void tsToFile(tStatistic statistic, int tNum)
{
	string filename = "transmitter" + to_string(tNum) + ".txt";
	ofstream out;
	out.open(filename);
	out << "Transmitter " << tNum << ", statistics:" << endl;
	out << "______________________________" << endl;
	out << "Frames sent: " << statistic.sendFrames << endl;
	out << "Distribution in time: ";
	for (size_t i = 0; i < statistic.frameDistribution.size(); i++)
	{
		out << statistic.frameDistribution[i] << " ";
	}
	out << "\nPrio 1 distribution: ";
	for (size_t i = 0; i < statistic.prio1Distribution.size(); i++)
	{
		out << statistic.prio1Distribution[i] << " ";
	}
	out << "\nPrio 2 distribution: ";
	for (size_t i = 0; i < statistic.prio2Distribution.size(); i++)
	{
		out << statistic.prio2Distribution[i] << " ";
	}
	out << "\nPrio 3 distribution: ";
	for (size_t i = 0; i < statistic.prio3Distribution.size(); i++)
	{
		out << statistic.prio3Distribution[i] << " ";
	}
	out << "\nPrio 4 distribution: ";
	for (size_t i = 0; i < statistic.prio4Distribution.size(); i++)
	{
		out << statistic.prio4Distribution[i] << " ";
	}
	out << "\n\nReceiver 1: " << statistic.receiver1 << endl;
	out << "Receiver 2: " << statistic.receiver2 << endl;
	out << "Receiver 3: " << statistic.receiver3 << endl;
	out << "Receiver 4: " << statistic.receiver4 << endl;
	out << "\nPriority 1: " << statistic.prio1 << endl;
	out << "Priority 2: " << statistic.prio2 << endl;
	out << "Priority 3: " << statistic.prio3 << endl;
	out << "Priority 4: " << statistic.prio4 << endl;
	out << "\nGroup 1: " << statistic.group1 << endl;
	out << "Group 2: " << statistic.group2 << endl;
	out << "Group 3: " << statistic.group3 << endl;

	out.close();
}

void generator(int tNum, int simulatiomTime, SYSTEMTIME start, transmitter t, mutex & m, vector<frame>& sBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	SYSTEMTIME st;

	//int A; // числитель
	//int B; // знаминатель, A/B - веро€тность по€влени€ кадра

	int y; 
	double v;
	int maxLam;
	int lam;

	y = (t.minFrame + t.maxFrame) / 2 * 8 + IPGBITS;
	v = y / (ETHERNET_SPEED * 1000000.0);
	maxLam = 1 / v;
	lam = maxLam * t.intensity / 100;

	// суммарное значение интервалов между кадрами в микросекундах
	int sumInter = 1000000 - (v*100000* ETHERNET_SPEED*lam);

	
	// ищем число нулей
	/*int i = 0;
	int N = maxLam;
	while (N > 0)
	{
		N = N / 10;
		i++;
	}*/

	//int mnojetel = pow(10.0, i);

	//B = ETHERNET_SPEED * 1000000 / y * simulatiomTime;
	//A = B * t.intensity / 100;
	
	int delay;
	//int averageDelay; // cредн€€ задержка
	//averageDelay = round(y / SLOWDOWN_COEF);

	if (t.intensity == 0)
		return;

	int chance; // шанс выдачи кадра
	frame newFrame; // кадр дл€ передачи
	
	tStatistic statistic{};



	do
	{
		/*double x = ((double)rand() / (RAND_MAX));
		delay = log(x) / lam * mnojetel * (-1);*/

		if (sumInter > 0)
		{
			delay = rand() / sumInter;
			sumInter -= delay;
			Sleep(static_cast<DWORD>(delay));
		}

		// длина кадра
		newFrame.length = (rand() % (t.maxFrame - t.minFrame + 1))
			+ t.minFrame;

		// логический сегмент получатель
		if (t.receiver == receivers::RANDOM)
		{
			int rec;
			do
			{
				rec = rand() % 4 + 1;
			} while (rec == tNum);
			newFrame.receiver = rec;
		}
		if (t.receiver == receivers::ONE)
			newFrame.receiver = 1;
		if (t.receiver == receivers::TWO)
			newFrame.receiver = 2;
		if (t.receiver == receivers::THREE)
			newFrame.receiver = 3;
		if (t.receiver == receivers::FOUR)
			newFrame.receiver = 4;

		// назначение приоритета
		if (t.globalPrio == onOffSwitch::ON) // глобального приоритета дл€ всех кадров сегмента 
		{
			if (t.globalPrioValue == globalPrioValues::ONE)
				newFrame.prio = 1;
			else if (t.globalPrioValue == globalPrioValues::TWO)
				newFrame.prio = 2;
			else if (t.globalPrioValue == globalPrioValues::THREE)
				newFrame.prio = 3;
			else if (t.globalPrioValue == globalPrioValues::FOUR)
				newFrame.prio = 4;
			else
				newFrame.prio = rand() % 4 + 1;
		}
		else
		{
			// перва€ группа
			if (newFrame.length >= 72 and newFrame.length < PRIO_TRASHOLD_ONE)
			{
				if (t.groupOne == insidePrioValues::RANDOM)
					newFrame.prio = rand() % 3 + 1;
				else if (t.groupOne == insidePrioValues::ONE)
					newFrame.prio = 1;
				else if (t.groupOne == insidePrioValues::TWO)
					newFrame.prio = 2;
				else if (t.groupOne == insidePrioValues::THREE)
					newFrame.prio = 3;
			}
			// втора€ группа
			if (newFrame.length >= PRIO_TRASHOLD_ONE and newFrame.length < PRIO_TRASHHOLD_TWO)
			{
				if (t.groupTwo == insidePrioValues::RANDOM)
					newFrame.prio = rand() % 3 + 1;
				else if (t.groupTwo == insidePrioValues::ONE)
					newFrame.prio = 1;
				else if (t.groupTwo == insidePrioValues::TWO)
					newFrame.prio = 2;
				else if (t.groupTwo == insidePrioValues::THREE)
					newFrame.prio = 3;
			}
			// треть€ группа
			if (newFrame.length >= PRIO_TRASHHOLD_TWO and newFrame.length <= 1526)
			{
				if (t.groupThree == insidePrioValues::RANDOM)
					newFrame.prio = rand() % 3 + 1;
				else if (t.groupThree == insidePrioValues::ONE)
					newFrame.prio = 1;
				else if (t.groupThree == insidePrioValues::TWO)
					newFrame.prio = 2;
				else if (t.groupThree == insidePrioValues::THREE)
					newFrame.prio = 3;
			}
		}
		// расчет задаржки передачи кадра
		delay = round((newFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);

		Sleep(static_cast<DWORD>(delay));

		// врем€ полной выдачи кадра
		GetSystemTime(&newFrame.sendTime);
		GetSystemTime(&newFrame.someTime);

		// добавл€ем кадр в буффер коммутатора
		m.lock();
		sBuffer.push_back(newFrame);
		m.unlock();

		//подсчет статистики
		writeStatistic(statistic, newFrame, getMilliSeconds(start), stop, simulatiomTime);

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	tsToFile(statistic, tNum);
}

void showTime(int simulationTime)
{
	for (int i = 0; i < simulationTime*SLOWDOWN_COEF; i++)
	{
		cout << "time: " << i << " sec\r";
		Sleep(1000);
	}
}

int getMin(vector<int> v)
{
	if (v.size() != 0) 
	{
		int min = v[0];
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] < min)
				min = v[i];
		}
		return min;
	}
	else
		return 0;
}

int getMax(vector<int> v)
{
	if (v.size() != 0)
	{
		int max = v[0];
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] > max)
				max = v[i];
		}
		return max;
	}
	else
		return 0;
}

double getAve(vector<int> v)
{
	int ave = 0;
	for (size_t i = 0; i < v.size(); i++)
		ave += v[i];

	if (v.size() != 0)
		return ave / v.size();
	else
		return 0;
}

