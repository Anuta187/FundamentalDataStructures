#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <chrono>


struct auditorium
{
	char litera;
	int num;
};

struct fullname
{
	std::string lastname;
	std::string firstname;
	std::string secondname;
};

struct times
{
	int hour;
	int minute;
};

struct list
{
	auditorium room;
	fullname name;
	times time;

	friend bool operator>(const list& left, const list& right) {
		return ((left.room.litera > right.room.litera) ||
			((left.room.litera == right.room.litera) && (left.room.num > right.room.num)) ||
			((left.room.litera == right.room.litera) && (left.room.num == right.room.num)) &&
			((left.name.secondname > right.name.secondname) ||
				((left.name.secondname == right.name.secondname) && (left.name.firstname >
					right.name.firstname)) ||
				((left.name.secondname == right.name.secondname) &&
					(left.name.firstname == right.name.firstname) &&
					(left.name.lastname > right.name.lastname))));
	}

	friend bool operator<(const list& left, const list& right) {
		return right > left;
	}
};

void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
}

void GetArray(list*& record, int size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	getline(file, line);
	int i = 0;
	while (i != size)
	{
		getline(file, line, ' ');
		record[i].room.litera = line[0];
		std::string number = line.erase(0, 1);
		record[i].room.num = stoi(number);
		getline(file, line, ' ');
		record[i].name.lastname = line;
		getline(file, line, ' ');
		record[i].name.firstname = line;
		getline(file, line, ' ');
		record[i].name.secondname = line;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line);
		record[i].time.minute = stoi(line);
		i++;
	}
	file.close();
}


void PutArray(list*& record, double time, int size, std::string filename, bool flag)
{
	std::ofstream(file);
	file.open(filename);
	file << time << "s\n";
	!flag ? file << "stable\n" : file << "unstable\n";
	for (int i = 0; i < size; i++)
	{
		file << record[i].room.litera << record[i].room.num << " ";
		file << record[i].name.lastname << " " << record[i].name.firstname << " " << record[i].name.secondname;
		file << record[i].time.hour << ":" << record[i].time.minute << std::endl;
	}
	file.close();
}
void Compare(bool flagS, bool flagI, double timeS, double timeI, std::string filename)//сравнение по времени и стабильности
{
	std::ofstream(file);
	file.open(filename);
	file << "               Shell sort                  Selection sort\n";
	file << "stable:       ";
	flagS == false ? file << "stable" : file << "unstable";
	flagI == false ? file << "                         stable\n" : file << "                       unstable\n";
	file << "time:        " << timeS << "                            " << timeI << std::endl;
	if (timeS < timeI)
		file << "Shell sort faster than Selection sort";
	if (timeS > timeI)
		file << "Selection sort faster than Shell sort";
	if (timeS == timeI)
		file << "Shell sort equal Selection sort";
	file.close();
}

void StableShell(list* record, int size, bool& flag)// проверка стабильности
{
	list temp;
	flag = false;
	int d = size;
	for (d / 2; d > 0; d /= 2)
	{
		for (int i = d; i < size; ++i)
		{
			if (std::tie(record[i].room.litera, record[i].room.num, record[i].name.lastname,
				record[i].name.firstname, record[i].name.secondname, record[i].time.hour,
				record[i].time.minute) == std::tie(record[i - 1].room.litera, record[i - 1].room.num,
					record[i - 1].name.lastname, record[i - 1].name.firstname, record[i - 1].name.secondname,
					record[i - 1].time.hour, record[i - 1].time.minute))
			{
				for (int j = i - d; j >= 0 && std::tie(record[j].room.litera, record[j].room.num,
					record[j].name.lastname, record[j].name.firstname, record[j].name.secondname,
					record[j].time.hour, record[j].time.minute) < std::tie(record[j + d].room.litera,
						record[j + d].room.num, record[j + d].name.lastname, record[j + d].name.firstname,
						record[j + d].name.secondname, record[j + d].time.hour, record[j + d].time.minute);
					j -= d)
				{
					temp = record[j];
					record[j] = record[j + d];
					record[j + d] = temp;
					flag = true;
				}
			}
		}
	}
}

void StableSelection(list* record, int size, bool& flag)
{
	list temp;
	flag = false;
	for (int i = 0; i < size; i++)
	{
		if (std::tie(record[i].room.litera, record[i].room.num, record[i].name.lastname,
			record[i].name.firstname, record[i].name.secondname, record[i].time.hour,
			record[i].time.minute) == std::tie(record[i - 1].room.litera, record[i - 1].room.num,
				record[i - 1].name.lastname, record[i - 1].name.firstname, record[i - 1].name.secondname,
				record[i - 1].time.hour, record[i - 1].time.minute))
		{
			for (int j = i; j > 0 && std::tie(record[j - 1].room.litera, record[j - 1].room.num,
				record[j - 1].name.lastname, record[j - 1].name.firstname,
				record[j - 1].name.secondname, record[j - 1].time.hour, record[j - 1].time.minute) >
				std::tie(record[j].room.litera, record[j].room.num, record[j].name.lastname,
					record[j].name.firstname, record[j].name.secondname, record[j].time.hour,
					record[j].time.minute); j--)
			{
				temp = record[j - 1];
				record[j - 1] = record[j];
				record[j] = temp;
				flag = true;
			}
		}
	}
}

void Shell(list*& record, int size)
{
	list temp;
	int d = size;
	for (d / 2; d > 0; d /= 2)
	{
		for (int i = d; i < size; ++i)
		{
			for (int j = i - d; j >= 0 && std::tie(record[j].room.litera, record[j].room.num) <
				std::tie(record[j + d].room.litera, record[j + d].room.num); j -= d)
			{
				temp = record[j];
				record[j] = record[j + d];
				record[j + d] = temp;
			}

		}
	}
	d = size;
	for (d / 2; d > 0; d /= 2)
	{
		for (int i = d; i < size; ++i)
		{
			if (std::tie(record[i].room.litera, record[i].room.num) ==
				std::tie(record[i - 1].room.litera, record[i - 1].room.num))
			{
				for (int j = i - d; j >= 0 && std::tie(record[j].name.lastname,
					record[j].name.firstname, record[j].name.secondname) <
					std::tie(record[j + d].name.lastname, record[j + d].name.firstname,
						record[j + d].name.secondname); j -= d)
				{
					temp = record[j];
					record[j] = record[j + d];
					record[j + d] = temp;
				}
			}
		}
		for (int i = d; i < size; ++i)
		{
			for (int j = i - d; j >= 0 && std::tie(record[j].room.litera, record[j].room.num) <
				std::tie(record[j + d].room.litera, record[j + d].room.num); j -= d)
			{
				temp = record[j];
				record[j] = record[j + d];
				record[j + d] = temp;
			}
		}
	}
}


void SelectionSort(list*& record, int size)
{

	for (int i = 0; i < size - 1; i++)
	{
		list max = record[i];
		int imax = i;
		for (auto j = i + 1; j < size; ++j) {
			if (record[j] > max) {
				max = record[j];
				imax = j;
			}
		}
		list temp = record[imax];
		record[imax] = record[i];
		record[i] = temp;
	}
}


void ShellTimer(double& time, list*& record, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	Shell(record, size);
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void SelectionTimer(double& time, list*& record, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	SelectionSort(record, size);
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	bool flagS, flagI;
	double timeS, timeI, time;
	std::ifstream file;
	file.open("Input.txt");
	GetSize(size, "Input.txt");
	list* record = new list[size];

	GetArray(record, size, "Input.txt");
	StableShell(record, size, flagS);
	ShellTimer(timeS, record, size);
	PutArray(record, timeS, size, "Output_Shell.txt", flagS);

	GetArray(record, size, "Input.txt");
	StableSelection(record, size, flagI);
	SelectionTimer(timeI, record, size);
	PutArray(record, timeI, size, "Output_Selection.txt", flagI);

	Compare(flagS, flagI, timeS, timeI, "Compare.txt");
	file.close();
	return 0;
}
