//still needs to print the output
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void pushToClock(vector<string> p, vector<int> &cv, int msgs[]);

int main() {
	
	//test case
	vector<string> p0, p1, p2;
	vector<int> c0, c1, c2;

	p0 = { "a", "s1", "r3", "b" };
	p1 = { "c", "r2", "s3" };
	p2 = { "r1", "d", "s2", "e" };

	//n = # of processes (3)
	//m = # of events (4)
	//maximum # of send messages can be n*m

	//hold logical clock value of send messages
	int sMessages[12];

	//initialize array to 0
	for (int i = 0; i < 12; i++)
	{
		sMessages[i] = 0;
	}

	//push clock values until the process and clock vectors are the same size
	while ((p0.size() != c0.size()) || (p1.size() != c1.size()) || (p2.size()) != c2.size())
	{
		//vectors aren't same size, so clear the clock vectors so we don't
		//write too many values to them
		c0.clear();
		c1.clear();
		c2.clear();

		//push values to clock once for each process
		pushToClock(p0, c0, sMessages);
		pushToClock(p1, c1, sMessages);
		pushToClock(p2, c2, sMessages);
	}

	system("pause");
	return 0;
}

//push clock values into clock vector
void pushToClock(vector<string> p, vector<int> &cv, int msgs[])
{
	int clockCount = 1;

	for (int i = 0; i < p.size(); i++)
	{
		//find first letter of string
		char c = p[i][0];

		//if send message, store in an array for access later
		if (c == 's')
		{
			p[i].erase(0, 1);
			msgs[stoi(p[i])] = clockCount;
			cv.push_back(clockCount);
			clockCount++;
		}
		
		//check if clock value is saved for indexed send message
		//if not, break the loop
		else if (c == 'r')
		{
			p[i].erase(0, 1);
			if (msgs[stoi(p[i])] == 0)
			{
				i = p.size();
			}
			else
			{
				clockCount = msgs[stoi(p[i])] + 1;
				cv.push_back(clockCount);
				clockCount++;
			}
		}

		//continue loop if internal event
		else
		{
			cv.push_back(clockCount);
			clockCount++;
		}
	}
}
