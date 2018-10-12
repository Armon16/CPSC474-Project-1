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
void testCase(int cMatrix[n][m], string pMatrix[n][m]);

int main() {
	bool temp;
	//test case 1 -- valid
	int cMatrix[n][m] = { { 1, 2, 8, 9 },{ 1, 6, 7, 0 },{ 3, 4, 5, 6 } };
	
	//test case 2 -- valid
	int cMatrix1[n][m] = { { 1, 2, 8, 9 },{ 1, 6, 7, 0 },{ 2, 3, 4, 5 } };
	
	//test case 3 -- invalid
	int cMatrix2[n][m] = { { 1, 2, 8, 9 },{ 1, 6, 7, 0 },{ 2, 4, 5, 6 } };
	string pMatrix[n][m]; //will hold process values

	testCase(cMatrix, pMatrix);
	testCase(cMatrix1, pMatrix);
	testCase(cMatrix2, pMatrix);
	

	cout << "Press enter to continue: ";
	cin.ignore();
	return 0;
}

void pushProcess(string p[n][m], int c[n][m], int highest)

{
	string internalEvent = "internal"; //store word for internal events
	int highC = 0; //highest clock value found so far
	int sCount = 0; //number of send messages found
	int rCount = 0; //number of receive messages found
	int outerIndex = 1;
	bool exitAll = false; //boolean to exit all loops

						  //loop through for as many receive events that are found
	for (int x = 0; x < outerIndex && !exitAll; x++)
	{
		rCount = 0;

		//loop for each process
		for (int i = 0; i < n && !exitAll; i++)
		{
			//loop for each event
			for (int j = 0; j < m && !exitAll; j++)
			{
				//check if first event in a process
				if (j == 0 && c[i][j] == 1)
				{
					//if the process is "null", overwrite
					//if it already stores a value, do not overwrite
					if (p[i][j] == "null")
					{
						//mark as internal event
						p[i][j] = internalEvent;
					}
					//count the highest clock that we've encountered
					if (c[i][j] > highC)
						highC = c[i][j];
				}
				//if the first event is a receive event
				else if (j == 0 && c[i][j] != 1)
				{
					//if the event is "null", overwrite with receive
					//if the event is already filled with a value, ignore
					if (p[i][j] == "null")
					{
						rCount++;
						j = foundRecEvent(c, p, i, j, highC, sCount);
					}
				}
				//check to see if events are consecutive
				else if (c[i][j - 1] == (c[i][j] - 1))
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
					rCount++;
					j = foundRecEvent(c, p, i, j, highC, sCount);
				}


				//if we've encountered the highest clock count, exit all loops
				//so that we don't overwrite events
				if (highest == highC) //c[i][j]
				{
					exitAll = true;
				}
			}
		}

		//change the outmost forloop index for each receive event found
		outerIndex = ++rCount;

	}
}

//reassign internal events as send messages and receive messages
int foundRecEvent(int c[n][m], string p[n][m], int i, int j, int &hC, int &sC)
{
	stringstream ss;
	//if we have found a matching send event
	if (hC >= c[i][j] - 1)
	{
		//mark that we have found a send event
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
		p[i][j] = "r" + ss.str(); // process = r + send index
		ss.clear(); //clear the string buffer for next time

					//adjust the highest clock count
		if (c[i][j] > hC)
			hC = c[i][j];
	}
	//no matching send found
	else
	{
		j = m; // exit loop
	}

	return j;
}

//change words from "internal" to letters
void changeInternals(string p[n][m])
{
	char ch = 'a';

	//loop through matrix and reassign values to remaining
	//internal events
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

void testCase(int cMatrix[n][m], string pMatrix[n][m])
{
	bool invalid = false;
	int highest = 0;

	bool errorArr[n*m];

	//set bool array to false
	for (int i = 0; i < n*m; i++)
	{
		errorArr[i] = false;
	}

	//for every clock value found, store true in errorArray
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
			invalid = true;
		}
	}

	if (!invalid)
	{
		pushProcess(pMatrix, cMatrix, highest);
		changeInternals(pMatrix);

		//print matrix
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << pMatrix[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl;
	}
}
