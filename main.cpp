//still needs to print the output
#include <iostream>
#include <string>
#include <vector> 

using namespace std;

const extern int n = 3; //no more than 5
const extern int m = 4; //no more than 25

void pushClock(string p[n][m], int c[n][m], int msgs[], int r);

int main() {

	//test case
	vector<string> p0, p1, p2;
	vector<int> c0, c1, c2;

	//
	string pMatrix[n][m] = { { "a", "s1", "r3", "b" }, { "c", "r2", "s3", "NULL" }, { "r1", "d", "s2", "e" } };
	int cMatrix[n][m];

	//initialize cMatrix to 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cMatrix[i][j] = 0;
		}
	}

	//hold logical clock value of send messages
	int sMessages[24];
	int rCount = 0;

	//initialize array to 0
	for (int i = 0; i < 24; i++)
	{
		sMessages[i] = 0;
	}

	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < m; b++)
		{
			if (pMatrix[a][b][0] == 'r')
				rCount++;
		}
	}

	pushClock(pMatrix, cMatrix, sMessages, rCount);
	cout << "FUCKING SUCCESS FINALLY" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << cMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Press enter to continue: ";
	cin.ignore();
	return 0;
}


void pushClock(string p[n][m], int c[n][m], int msgs[], int r)
{
	for (int abc = 0; abc < r; abc++)
	{
		//loops through the processes
		for (int i = 0; i < n; i++)
		{
			
			//set clock count to 1 for each new process
			int clockCount = 1;
			string tString = "";

			//loops through the events
			for (int j = 0; j < m; j++)
			{
				
				//find first letter of string
				char ch = p[i][j][0];

				//if send message, store in an array for access later
				if (ch == 's')
				{
					tString = p[i][j];
					p[i][j].erase(0, 1);
					msgs[stoi(p[i][j])] = clockCount;
					c[i][j] = clockCount;
					p[i][j] = tString;
					clockCount++;
				}

				//check if clock value is saved for indexed send message
				//if not, break the loop
				else if (ch == 'r')
				{
					tString = p[i][j];
					p[i][j].erase(0, 1);
					if (msgs[stoi(p[i][j])] == 0)
					{
						
						//sets iterator to max, loop won't repeat
						p[i][j] = tString;
						j = m;
						
					}
					else
					{
						
						//find the correlated send message in array and increment
						clockCount = msgs[stoi(p[i][j])] + 1;
						c[i][j] = clockCount;
						p[i][j] = tString;
						clockCount++;
					}
				}
				//check to see if null
				else if (ch == 'n' || ch == 'N')
				{
					
					string temp = "";
					//push string to all lower case
					for (int k = 0; k < p[i][j].size(); k++)
					{
						temp += tolower(p[i][j][k]);
					}

					if (temp == "null")
					{
						
						//move to next process
						j = m;
					}
					else
					{
						
						c[i][j] = clockCount;
						clockCount++;
					}
				}

				//continue loop if internal event
				else
				{
					
					c[i][j] = clockCount;
					clockCount++;
				}
			}
		}
	}
}
