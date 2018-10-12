//still needs to print the output
#include <iostream>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

const extern int n = 3; //no more than 5
const extern int m = 4; //no more than 25

void pushProcess(string p[n][m], int c[n][m], int highest);
int foundRecEvent(int c[n][m], string p[n][m], int i, int j, int &hC, int &sC);
void changeInternals(string p[n][m]);

int main() {


	//
	int cMatrix[n][m] = { { 1, 2, 8, 9 },{ 1, 6, 7, 0 },{ 2, 3, 4, 5 } };
	string pMatrix[n][m];
	int sCount, rCount = 0;
	int highest = 0;

	bool errorArr[n*m];

	//set bool array to false
	for (int i = 0; i < n*m; i++)
	{
		errorArr[i] = false;
	}

	//for every c value found, store true in errorArray
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			errorArr[cMatrix[i][j]] = true;
		}
	}

	//initialize pMatrix to 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			pMatrix[i][j] = "null";
		}
	}

	//find the highest clock value
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (cMatrix[i][j] > highest)
				highest = cMatrix[i][j];
		}
	}

	//if the array doesn't consist of consecutive numbers, then
	//the matrix is invalid
	for (int i = 1; i < highest; i++)
	{
		if (!errorArr[i])
		{
			cout << "Invalid matrix\n";
			system("pause");
			return 1;
		}
	}
	
	pushProcess(pMatrix, cMatrix, highest);
	changeInternals(pMatrix);
	cout << "SUCCESS FINALLY" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << pMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Press enter to continue: ";
	cin.ignore();
	return 0;
}

void pushProcess(string p[n][m], int c[n][m], int highest)

{
	string internalEvent = "internal";
	int highC = 0;
	int sCount = 0;
	int rCount = 0;
	int outerIndex = 1;
	bool exitAll = false;

	for (int x = 0; x < outerIndex && !exitAll; x++)
	{
		rCount = 0;
		//sCount = 0;

		//loop for each process
		for (int i = 0; i < n && !exitAll; i++)
		{
			//loop for each event
			for (int j = 0; j < m && !exitAll; j++)
			{
				//check if first event in a process
				if (j == 0 && c[i][j] == 1)
				{
					if (p[i][j] == "null")
					{
						//mark as internal event
						p[i][j] = internalEvent;
					}
					//count the highest clock that we've encountered
					if (c[i][j] > highC)
						highC = c[i][j];
				}
				else if (j == 0 && c[i][j] != 1)
				{
					//if the event is already filled with a value, ignore
					if (p[i][j] == "null")
					{
						rCount++;
						j = foundRecEvent(c, p, i, j, highC, sCount);
					}
				}				
				//check to see if events are consecutive
				else if (c[i][j-1] == (c[i][j] - 1))
				{
					//mark as internal event
					if (p[i][j] == "null")
						p[i][j] = internalEvent;
					//count the highest clock that we've encountered
					if (c[i][j] > highC)
						highC = c[i][j];
				}
				//if clock event is zero, leave remaining value as null in process matrix
				else if (c[i][j] == 0)
				{
					//exit inner loop
					j = m;
				}
				//hit a receive event
				else
				{					
					rCount++; // may not even need it
					j = foundRecEvent(c, p, i, j, highC, sCount);
				}

				
				//if highest number is found, exit all loops
				if (highest == highC) //c[i][j]
				{
					exitAll = true;
				}
			}
		}

		outerIndex = ++rCount;
		
	}
}

int foundRecEvent(int c[n][m], string p[n][m], int i, int j, int &hC, int &sC)
{
	stringstream ss;
	//if we have found a matching send event
	if (hC >= c[i][j] - 1)
	{
		//mark that we have found a receive and send event
		//rCount++;
		sC++;

		//find the send process in the clock matrix
		bool exitInner = false;
		bool exitOuter = false;
		for (int a = 0; a < n && !exitOuter; a++)
		{
			for (int b = 0; b < m && !exitInner; b++)
			{
				if (c[a][b] == (c[i][j] - 1))
				{
					//cast send count to string
					ss << sC;
					//process = s + send index
					p[a][b] = "s" + ss.str();
					exitInner = true; //break loop when found
				}
			}
			if (exitInner)
				exitOuter = true; //break outer loop
		}

		//add r to process matrix
		//ss << sC;
		p[i][j] = "r" + ss.str(); // process = r + send index
		ss.clear();

		if (c[i][j] > hC)
			hC = c[i][j];
	}
	//no matching send found
	else
	{
		j = m;
	}

	return j;
}

//change words from "internal" to letters
void changeInternals(string p[n][m])
{
	char ch = 'a';

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (p[i][j] == "internal")
			{
				p[i][j] = ch;
				ch++;
			}
		}
	}
}
