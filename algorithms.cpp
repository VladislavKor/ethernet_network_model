#include "algorithms.h"

void writeStatistic(sStatistic & statistic, frame f, int start, int stop, int simulationTime, SYSTEMTIME st, bool flag)
{
	int x;

	if (flag == true)
		statistic.accepted += 1;
	else
		statistic.transfered += 1;
	if (flag == true)
	{
		x = (getMilliSeconds(st) - getMilliSeconds(f.sendTime)) * 10;
		statistic.Delay.push_back(x);
		if (f.prio == 1)
			statistic.prio1Delay.push_back(x);
		if (f.prio == 2)
			statistic.prio2Delay.push_back(x);
		if (f.prio == 3)
			statistic.prio3Delay.push_back(x);
		if (f.prio == 4)
			statistic.prio4Delay.push_back(x);
	}
	else
	{
		x = (getMilliSeconds(st) - getMilliSeconds(f.someTime)) * 10;
		statistic.ProcessingTime.push_back(x);
		if (f.prio == 1)
			statistic.prio1PTime.push_back(x);
		if (f.prio == 2)
			statistic.prio2PTime.push_back(x);
		if (f.prio == 3)
			statistic.prio3PTime.push_back(x);
		if (f.prio == 4)
			statistic.prio4PTime.push_back(x);
	}

	int leftBorder = start;
	int rightBorder;
	int sendTime;
	x = (stop - start) / (10 * simulationTime);
	for (int i = 1; i <= (10 * simulationTime); i++)
	{
		sendTime = getMilliSeconds(st);
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

				statistic.returnedDistr.push_back(statistic.returned);
			}

			break;
		}
		leftBorder += x;
	}
}

void ssToFile(sStatistic statistic, int sNum, string mode)
{
	string filename = "switch" + to_string(sNum) + ".txt";
	ofstream out;
	out.open(filename);
	out << "Switch " << sNum << ", statistics:" << endl;
	out << "Mode: " << mode << endl;
	out << "______________________________" << endl;
	out << "Accepted frames: " << statistic.accepted << endl;
	out << "Transfered frames: " << statistic.transfered << endl;
	out << "Returned in buffer frames: " << statistic.returned << endl;
	out << "Total: " << statistic.accepted + statistic.transfered << endl;
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
	out << "\nReturned distribution: ";
	for (size_t i = 0; i < statistic.returnedDistr.size(); i++)
	{
		if (i == 0)
			out << statistic.returnedDistr[i] << " ";
		else
			out << statistic.returnedDistr[i] - statistic.returnedDistr[i-1] << " ";
		
	}
	out << "\n\nMin transmission delay: " << getMin(statistic.Delay) << " usec" << endl;
	out << "Max transmission delay: " << getMax(statistic.Delay) << " usec" << endl;
	out << "Average transmittion delay: " << getAve(statistic.Delay) << " usec" << endl;
	out << "Prio 1: min delay = " << getMin(statistic.prio1Delay);
	out << "; max delay = " << getMax(statistic.prio1Delay);
	out << "; average delay = " << getAve(statistic.prio1Delay) << "[usec]" << endl;
	out << "Prio 2: min delay = " << getMin(statistic.prio2Delay);
	out << "; max delay = " << getMax(statistic.prio2Delay);
	out << "; average delay = " << getAve(statistic.prio2Delay) << "[usec]" << endl;
	out << "Prio 3: min delay = " << getMin(statistic.prio3Delay);
	out << "; max delay = " << getMax(statistic.prio3Delay);
	out << "; average delay = " << getAve(statistic.prio3Delay) << "[usec]" << endl;
	out << "Prio 4: min delay = " << getMin(statistic.prio4Delay);
	out << "; max delay = " << getMax(statistic.prio4Delay);
	out << "; average delay = " << getAve(statistic.prio4Delay) << "[usec]" << endl;
	out << "\nMin processing delay: " << getMin(statistic.ProcessingTime) << " usec" << endl;
	out << "Max processing delay: " << getMax(statistic.ProcessingTime) << " usec" << endl;
	out << "Average processing delay: " << getAve(statistic.ProcessingTime) << " usec" << endl;
	out << "Prio 1: min delay = " << getMin(statistic.prio1PTime);
	out << "; max delay = " << getMax(statistic.prio1PTime);
	out << "; average delay = " << getAve(statistic.prio1PTime) << "[usec]" << endl;
	out << "Prio 2: min delay = " << getMin(statistic.prio2PTime);
	out << "; max delay = " << getMax(statistic.prio2PTime);
	out << "; average delay = " << getAve(statistic.prio2PTime) << "[usec]" << endl;
	out << "Prio 3: min delay = " << getMin(statistic.prio3PTime);
	out << "; max delay = " << getMax(statistic.prio3PTime);
	out << "; average delay = " << getAve(statistic.prio3PTime) << "[usec]" << endl;
	out << "Prio 4: min delay = " << getMin(statistic.prio4PTime);
	out << "; max delay = " << getMax(statistic.prio4PTime);
	out << "; average delay = " << getAve(statistic.prio4PTime) << "[usec]" << endl;
	out << "\nMin buffer length: " << getMin(statistic.bufferSize) << endl;
	out << "Max buffer length: " << getMax(statistic.bufferSize) << endl;
	out << "Average buffer length: " << getAve(statistic.bufferSize) << endl;
	out << "Buffer residue: " << statistic.residue << endl;

	out.close();
}

void fifo(int sNum, int simulatiomTime, SYSTEMTIME start, mutex & lm, mutex & m, mutex & rm, vector<frame>& slBuffer, vector<frame>& sBuffer, vector<frame>& srBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	SYSTEMTIME st;

	bool flag = false;

	int delay;

	frame currentFrame{};

	sStatistic statistic{};

	do
	{
		m.lock();
		if (!sBuffer.empty())
		{
			statistic.bufferSize.push_back(sBuffer.size());
			currentFrame = sBuffer[0];
			sBuffer.erase(sBuffer.begin());
			flag = true;
		}
		m.unlock();

		if (flag == true)
		{
			delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);

			if (currentFrame.receiver == sNum)
			{
				Sleep(static_cast<DWORD>(delay));
				
				// сбор статистики
				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);
				
			}
			if (currentFrame.receiver < sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				lm.lock();
				slBuffer.push_back(currentFrame);
				lm.unlock();
			}
			if (currentFrame.receiver > sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				rm.lock();
				srBuffer.push_back(currentFrame);
				rm.unlock();
			}
			flag = false;
		}

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	statistic.residue = sBuffer.size();
	ssToFile(statistic, sNum, "fifo");
}

void lifo(int sNum, int simulatiomTime, SYSTEMTIME start, mutex & lm, mutex & m, mutex & rm, vector<frame>& slBuffer, vector<frame>& sBuffer, vector<frame>& srBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	SYSTEMTIME st;

	bool flag = false;

	int delay;

	frame currentFrame{};

	sStatistic statistic{};

	do
	{
		m.lock();
		if (!sBuffer.empty())
		{
			statistic.bufferSize.push_back(sBuffer.size());
			currentFrame = sBuffer[sBuffer.size() - 1];
			sBuffer.pop_back();
			flag = true;
		}
		m.unlock();

		if (flag == true)
		{
			delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);

			if (currentFrame.receiver == sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				// сбор статистики
				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);

			}
			if (currentFrame.receiver < sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				lm.lock();
				slBuffer.push_back(currentFrame);
				lm.unlock();
			}
			if (currentFrame.receiver > sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				rm.lock();
				srBuffer.push_back(currentFrame);
				rm.unlock();
			}
			flag = false;
		}

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	statistic.residue = sBuffer.size();
	ssToFile(statistic, sNum, "lifo");
}

void relativePrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex & lm, mutex & m, mutex & rm, vector<frame>& slBuffer, vector<frame>& sBuffer, vector<frame>& srBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	SYSTEMTIME st;

	bool flag = false;
	bool flag2 = false;

	int delay;

	frame currentFrame{};

	sStatistic statistic{};

	do
	{
		m.lock();
		if (!sBuffer.empty())
		{
			statistic.bufferSize.push_back(sBuffer.size());
			for (size_t prio = 1; prio <= 4; prio++)
			{
				for (size_t i = 0; i < sBuffer.size(); i++)
				{
					if (sBuffer[i].prio == prio)
					{
						currentFrame = sBuffer[i];
						sBuffer.erase(sBuffer.begin() + i);
						flag2 = true;
						break;
					}
				}
				if (flag2 == true)
					break;
			}
			flag = true;
		}
		m.unlock();

		if (flag == true)
		{
			delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);

			if (currentFrame.receiver == sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				// сбор статистики
				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);

			}
			if (currentFrame.receiver < sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				lm.lock();
				slBuffer.push_back(currentFrame);
				lm.unlock();
			}
			if (currentFrame.receiver > sNum)
			{
				Sleep(static_cast<DWORD>(delay));

				GetSystemTime(&st);
				writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
				currentFrame.someTime = st;

				rm.lock();
				srBuffer.push_back(currentFrame);
				rm.unlock();
			}
			flag = false;
			flag2 = false;
		}

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	statistic.residue = sBuffer.size();
	ssToFile(statistic, sNum, "relative prio");
}

void absolutePrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex & lm, mutex & m, mutex & rm, vector<frame>& slBuffer, vector<frame>& sBuffer, vector<frame>& srBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	SYSTEMTIME st;

	bool ftFlag = false; // кадр уже передается
	bool flag = false; // взяли кадр

	int delay;

	int counter = 0;

	frame currentFrame{};
	frame copyCFrame{};

	sStatistic statistic{};

	do
	{
		m.lock();
		if (!sBuffer.empty())
		{
			if (ftFlag == false) // кадр еще не передавался
			{
				for (size_t prio = 1; prio <= 4; prio++)
				{
					for (size_t i = 0; i < sBuffer.size(); i++)
					{
						if (sBuffer[i].prio == prio)
						{
							statistic.bufferSize.push_back(sBuffer.size());
							currentFrame = sBuffer[i];
							sBuffer.erase(sBuffer.begin() + i);
							delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
							flag = true;
							break;
						}
					}
					if (flag == true)
						break;
				}
			}
			else // уже передаем какойто кадр
			{
				for (int prio = 1; prio < currentFrame.prio; prio++)
				{
					for (size_t i = 0; i < sBuffer.size(); i++)
					{
						if (sBuffer[i].prio == prio) // нашли кадр с большим приоритетом
						{
							statistic.returned += 1;
							statistic.bufferSize.push_back(sBuffer.size());
							copyCFrame = currentFrame;
							currentFrame = sBuffer[i];
							sBuffer.erase(sBuffer.begin() + i);
							sBuffer.insert(sBuffer.begin(), copyCFrame);
							delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
							flag = true;
							break;
						}
					}
					if (flag == true)
						break;
				}
			}
		}
		m.unlock();

		if (flag == true)
		{
			if (currentFrame.receiver == sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
			if (currentFrame.receiver < sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					lm.lock();
					slBuffer.push_back(currentFrame);
					lm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					lm.lock();
					slBuffer.push_back(currentFrame);
					lm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
			if (currentFrame.receiver > sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					rm.lock();
					srBuffer.push_back(currentFrame);
					rm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					rm.lock();
					srBuffer.push_back(currentFrame);
					rm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
		}

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	statistic.residue = sBuffer.size();
	ssToFile(statistic, sNum, "absolute prio");
}

void mixedPrio(int sNum, int simulatiomTime, SYSTEMTIME start, mutex & lm, mutex & m, mutex & rm, vector<frame>& slBuffer, vector<frame>& sBuffer, vector<frame>& srBuffer)
{
	int stop = getMilliSeconds(start) + simulatiomTime * SLOWDOWN_COEF * MILLI_IN_SEC;

	int Absolute = 2;
	int Relative = 0;

	SYSTEMTIME st;

	bool ftFlag = false; // кадр уже передается
	bool flag = false; // взяли кадр

	int delay;

	int counter = 0;

	frame currentFrame{};
	frame copyCFrame{};

	sStatistic statistic{};

	do
	{
		m.lock();
		if (!sBuffer.empty())
		{
			if (ftFlag == false) // кадр еще не передавался
			{
				// абсолютные приоритеты
				for (size_t prio = 1; prio <= Absolute; prio++)
				{
					for (size_t i = 0; i < sBuffer.size(); i++)
					{
						if (sBuffer[i].prio == prio)
						{
							statistic.bufferSize.push_back(sBuffer.size());
							currentFrame = sBuffer[i];
							sBuffer.erase(sBuffer.begin() + i);
							delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
							flag = true;
							break;
						}
					}
					if (flag == true)
						break;
				}
				if (flag == false)// относительные приоритеты
				{
					for (size_t prio = Absolute + 1; prio <= Relative; prio++)
					{
						for (size_t i = 0; i < sBuffer.size(); i++)
						{
							if (sBuffer[i].prio == prio)
							{
								statistic.bufferSize.push_back(sBuffer.size());
								currentFrame = sBuffer[i];
								sBuffer.erase(sBuffer.begin() + i);
								delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
								flag = true;
								break;
							}
						}
						if (flag == true)
							break;
					}
				}
				if (flag == false)// без приоритетов
				{
					statistic.bufferSize.push_back(sBuffer.size());
					currentFrame = sBuffer[0];
					sBuffer.erase(sBuffer.begin());
					delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
					flag = true;
				}
			}
			else // уже передаем какойто кадр
			{
				// абсолютный приоритет
				for (int prio = 1; prio < Absolute; prio++)
				{
					for (size_t i = 0; i < sBuffer.size(); i++)
					{
						if (sBuffer[i].prio < currentFrame.prio) // нашли кадр с большим приоритетом
						{
							statistic.returned += 1;
							statistic.bufferSize.push_back(sBuffer.size());
							copyCFrame = currentFrame;
							currentFrame = sBuffer[i];
							sBuffer.erase(sBuffer.begin() + i);
							sBuffer.insert(sBuffer.begin(), copyCFrame);
							delay = round((currentFrame.length * 8 + IPGBITS) / SLOWDOWN_COEF);
							flag = true;
							break;
						}
					}
					if (flag == true)
						break;
				}
			}
		}
		m.unlock();

		if (flag == true)
		{
			if (currentFrame.receiver == sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, true);
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
			if (currentFrame.receiver < sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					lm.lock();
					slBuffer.push_back(currentFrame);
					lm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					lm.lock();
					slBuffer.push_back(currentFrame);
					lm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
			if (currentFrame.receiver > sNum)
			{
				if (delay - TIMESLOT > 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					delay -= TIMESLOT;
					ftFlag = true; // кадр не выдан до конца
				}
				else if (delay - TIMESLOT == 0)
				{
					Sleep(static_cast<DWORD>(TIMESLOT));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					rm.lock();
					srBuffer.push_back(currentFrame);
					rm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
				else
				{
					Sleep(static_cast<DWORD>(delay));
					GetSystemTime(&st);
					writeStatistic(statistic, currentFrame, getMilliSeconds(start), stop, simulatiomTime, st, false);
					currentFrame.someTime = st;
					rm.lock();
					srBuffer.push_back(currentFrame);
					rm.unlock();
					flag = false;
					ftFlag = false; // кадр  выдан
				}
			}
		}

		GetSystemTime(&st);
	} while (getMilliSeconds(st) < stop);

	statistic.residue = sBuffer.size();
	ssToFile(statistic, sNum, "mixed prio");
}
