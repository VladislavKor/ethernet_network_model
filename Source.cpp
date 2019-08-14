#include "constants.h"
#include "functions.h"
#include "algorithms.h"
#include <iostream>

using namespace std;

int main()
{
	int simulationTime = 0;

	transmitter t1{};
	transmitter t2{};
	transmitter t3{};
	transmitter t4{};

	vector<switchModes> sModes;
	sModes.clear();

	// считываем параметры
	if (!readParameters(simulationTime, t1, t2, t3, t4, sModes))
	{
		cout << "File parameters.txt not found" << endl;
		return 0;
	}

	// вывод параметров
	cout << "\tNetwork model parameters" << endl;
	cout << "Simulation time = " << simulationTime << " sec" << endl;
	cout << "\nTransmitter 1:" << endl;
	printTransmitter(t1);
	cout << "\nTransmitter 2:" << endl;
	printTransmitter(t2);
	cout << "\nTransmitter 3:" << endl;
	printTransmitter(t3);
	cout << "\nTransmitter 4:" << endl;
	printTransmitter(t4);
	cout << "\nSwitch modes:" << endl;
	for (size_t i = 0; i < sModes.size(); i++)
	{
		cout << "Switch " << i + 1 << ": ";
		if (sModes[i] == switchModes::FIFO)
			cout << "FIFO" << endl;
		if (sModes[i] == switchModes::LIFO)
			cout << "LIFO" << endl;
		if(sModes[i] == switchModes::RELPRIO)
			cout << "RELPRIO" << endl;
		if (sModes[i] == switchModes::ABSPRIO)
			cout << "ABSPRIO" << endl;
		if (sModes[i] == switchModes::MIXED)
			cout << "MIXED" << endl;
	}

	cout << endl;
	// запуск моделирования
	string choice;
	while (true)
	{
		cout << "Start simulation? y/n: ";
		cin >> choice;
		if (choice == "y")
			break;
		if (choice == "n")
		{
			cout << "Exit" << endl;
			system("pause");
			return 0;
		}
	}

	mutex m1;
	mutex m2;
	mutex m3;
	mutex m4;

	vector<frame> sb1;
	vector<frame> sb2;
	vector<frame> sb3;
	vector<frame> sb4;



	// генераторы кадров
	thread g1; 
	thread g2;
	thread g3;
	thread g4;

	// коммутаторы
	thread s1;
	thread s2;
	thread s3;
	thread s4;

	// визуализатор времени ожидания
	thread t100;
	cout << "Simulation time ~ 100 sec" << endl;

	srand(static_cast<unsigned int>(time(0)));

	SYSTEMTIME st;
	GetSystemTime(&st);


	g1 = thread(generator, 1, simulationTime, st, t1, ref(m1), ref(sb1));
	g2 = thread(generator, 2, simulationTime, st, t2, ref(m2), ref(sb2));
	g3 = thread(generator, 3, simulationTime, st, t3, ref(m3), ref(sb3));
	g4 = thread(generator, 4, simulationTime, st, t4, ref(m4), ref(sb4));

	// первый коммутатор
	switch (sModes[0])
	{
	case switchModes::FIFO:
	{
		s1 = thread(fifo, 1, simulationTime, st, ref(m1), ref(m1), ref(m2), ref(sb1), ref(sb1), ref(sb2));
		break;
	}
	case switchModes::LIFO:
	{
		s1 = thread(lifo, 1, simulationTime, st, ref(m1), ref(m1), ref(m2), ref(sb1), ref(sb1), ref(sb2));
		break;
	}
	case switchModes::RELPRIO:
	{
		s1 = thread(relativePrio, 1, simulationTime, st, ref(m1), ref(m1), ref(m2), ref(sb1), ref(sb1), ref(sb2));
		break;
	}
	case switchModes::ABSPRIO:
	{
		s1 = thread(absolutePrio, 1, simulationTime, st, ref(m1), ref(m1), ref(m2), ref(sb1), ref(sb1), ref(sb2));
		break;
	}
	case switchModes::MIXED:
	{
		s1 = thread(mixedPrio, 1, simulationTime, st, ref(m1), ref(m1), ref(m2), ref(sb1), ref(sb1), ref(sb2));
		break;
	}
	default:
		break;
	}

	// второй коммутатор
	switch (sModes[1])
	{
	case switchModes::FIFO:
	{
		s2 = thread(fifo, 2, simulationTime, st, ref(m1), ref(m2), ref(m3), ref(sb1), ref(sb2), ref(sb3));
		break;
	}
	case switchModes::LIFO:
	{
		s2 = thread(lifo, 2, simulationTime, st, ref(m1), ref(m2), ref(m3), ref(sb1), ref(sb2), ref(sb3));
		break;
	}
	case switchModes::RELPRIO:
	{
		s2 = thread(relativePrio, 2, simulationTime, st, ref(m1), ref(m2), ref(m3), ref(sb1), ref(sb2), ref(sb3));
		break;
	}
	case switchModes::ABSPRIO:
	{
		s2 = thread(absolutePrio, 2, simulationTime, st, ref(m1), ref(m2), ref(m3), ref(sb1), ref(sb2), ref(sb3));
		break;
	}
	case switchModes::MIXED:
	{
		s2 = thread(mixedPrio, 2, simulationTime, st, ref(m1), ref(m2), ref(m3), ref(sb1), ref(sb2), ref(sb3));
		break;
	}
	default:
		break;
	}

	// третий комутатор
	switch (sModes[2])
	{
	case switchModes::FIFO:
	{
		s3 = thread(fifo, 3, simulationTime, st, ref(m2), ref(m3), ref(m4), ref(sb2), ref(sb3), ref(sb4));
		break;
	}
	case switchModes::LIFO:
	{
		s3 = thread(lifo, 3, simulationTime, st, ref(m2), ref(m3), ref(m4), ref(sb2), ref(sb3), ref(sb4));
		break;
	}
	case switchModes::RELPRIO:
	{
		s3 = thread(relativePrio, 3, simulationTime, st, ref(m2), ref(m3), ref(m4), ref(sb2), ref(sb3), ref(sb4));
		break;
	}
	case switchModes::ABSPRIO:
	{
		s3 = thread(absolutePrio, 3, simulationTime, st, ref(m2), ref(m3), ref(m4), ref(sb2), ref(sb3), ref(sb4));
		break;
	}
	case switchModes::MIXED:
	{
		s3 = thread(mixedPrio, 3, simulationTime, st, ref(m2), ref(m3), ref(m4), ref(sb2), ref(sb3), ref(sb4));
		break;
	}
	default:
		break;
	}

	// четвертый коммутатор
	switch (sModes[3])
	{
	case switchModes::FIFO:
	{
		s4 = thread(fifo, 4, simulationTime, st, ref(m3), ref(m4), ref(m4), ref(sb3), ref(sb4), ref(sb4));
		break;
	}
	case switchModes::LIFO:
	{
		s4 = thread(lifo, 4, simulationTime, st, ref(m3), ref(m4), ref(m4), ref(sb3), ref(sb4), ref(sb4));
		break;
	}
	case switchModes::RELPRIO:
	{
		s4 = thread(relativePrio, 4, simulationTime, st, ref(m3), ref(m4), ref(m4), ref(sb3), ref(sb4), ref(sb4));
		break;
	}
	case switchModes::ABSPRIO:
	{
		s4 = thread(absolutePrio, 4, simulationTime, st, ref(m3), ref(m4), ref(m4), ref(sb3), ref(sb4), ref(sb4));
		break;
	}
	case switchModes::MIXED:
	{
		s4 = thread(mixedPrio, 4, simulationTime, st, ref(m3), ref(m4), ref(m4), ref(sb3), ref(sb4), ref(sb4));
		break;
	}
	default:
		break;
	}

	t100 = thread(showTime, simulationTime);

	g1.join();
	g2.join();
	g3.join();
	g4.join();

	s1.join();
	s2.join();
	s3.join();
	s4.join();

	t100.join();

	system("pause");
	return 0;
}
