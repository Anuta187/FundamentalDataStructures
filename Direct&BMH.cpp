#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<vector>
# define NO_OF_CHARS 256

struct Auditorium
{
	char litera;
	int num;
};

struct sub
{
	std::string subj;
};

struct Times
{
	int hour;
	int minute;
};

struct List
{
	Auditorium room;
	std::string fullname;
	Times time;
	std::string object;
};

void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
};
void GetArray(List*& record, int size, std::string filename)
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
		std::string name = line;
		getline(file, line, ' ');
		name = name + " " + line;
		getline(file, line, ' ');
		record[i].fullname = name + " " + line;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line, ' ');
		record[i].time.minute = stoi(line);
		getline(file, line);
		record[i].object = line;
		i++;
	}
	file.close();
}

void PutArray(List*& record, double time, int size, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << time << "s\n";
	for (int i = 0; i < size; i++)
	{
		file << record[i].room.litera <<  record[i].room.num << " ";
		file << record[i].fullname << " ";
		file << record[i].time.hour << ":" << record[i].time.minute << std::endl;
		file << record[i].object << " ";
	}
	file.close();
};

void DirectSearch(std::string str, std::string pattern, int& res, int& m)
{
	int strl = str.length();
	int patl = pattern.length();
	res = -1;
	m = 0;
	for (int i = 0; i < strl - patl + 1; i++)
	{
		for (int j = 0; j < patl; j++)
		{
			if (pattern[j] != str[i + j])
				break;
			else if (j == patl - 1)
			{
				m = m + 1;
				res = i;
				break;
			}
		}
	}
}

void DirectTimer(List* record, double& time, std::string pattern, int size, int res1, int res2, int m1, int m2, std::string filename)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname, pattern, res1, m1);
		DirectSearch(record[i].object, pattern, res2, m2);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void Direct(List* record, std::string pattern, int size)
{
	int res1 = -1, m1 = 0, res2 = -1, m2 = 0, j = 0;
	double time = 0;
	List* listing1 = new List[size];
	DirectTimer(record, time, pattern, size, res1, res2, m1, m2, "OutputDirect.txt");
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname, pattern, res1, m1);
		DirectSearch(record[i].object, pattern, res2, m2);
		if ((res1 != -1 && m1 == 1) || (res2 != -1 && m2 == 1))
		{
			listing1[j] = record[i];
			j++;
		}
	}
	PutArray(listing1, time, j, "Output.txt");
}

void badCharHeuristic(std::string pattern, int size, std::vector<char>& badchar)
{
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)pattern[i]] = i;
}

void BMH(std::string str, std::string pattern, int& res, int& t, std::vector<char> badchar)
{
	int m = pattern.length();
	int n = str.length();

	res = -1;
	t = 0;

	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;
		while (j >= 0 && pattern[j] == str[s + j])
			j--;
		if (j < 0)
		{
			t++;
			res = 1;
			s += (s + m < n) ? m - badchar[str[s + m]] : 1;
		}
		else
			s += std::max(1, j - badchar[str[s + j]]);
	}
}

void BMHTimer(List* record, double& time, std::string pattern, int size, int res1, int res2, int m1, int m2, std::string filename)
{
	std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	badCharHeuristic(pattern, m, badchar);
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		BMH(record[i].fullname, pattern, res1, m1, badchar);
		BMH(record[i].object, pattern, res2, m2, badchar);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void BMH_search(List* record, std::string pattern, int size)
{
	List* listing2 = new List[size];
	double time = 0;
	int res1 = 0, res2 = 0, m1 = 0, m2 = 0, j=0;
	std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	DirectTimer(record, time, pattern, size, res1, res2, m1, m2, "OutputBMH.txt");
	badCharHeuristic(pattern, m, badchar);
	for (int i = 0; i < size; i++)
	{
		BMH(record[i].fullname, pattern, res1, m1, badchar);
		BMH(record[i].object, pattern, res2, m2, badchar);
		if ((res1 != -1 && m1==1)||(res2!=-1 && m2==1))
		{
			listing2[j] = record[i];
			j++;
		}
	}
	PutArray(listing2, time, j, "Output1.txt");
}

int main()
{
	int size{};
	double time{};
	int res1 = 0, res2 = 0, m1 = 0, m2 = 0;
	std::ifstream file;
	GetSize(size, "2input.txt");
	List* record1 = new List[size];

	GetArray(record1, size, "2input.txt");
	file.close();
	std::string pattern = "A";
	Direct(record1, pattern, size);
	BMH_search(record1, pattern, size);
}