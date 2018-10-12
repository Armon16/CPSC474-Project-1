# CPSC471-Project-1
# Anette Ulrichsen
# Georden Grabuskie
#Files: processToLC.cpp, LCtoProcess.cpp, processToLC.out, LCtoProcess.out, README.md

created an algorithm that assigns logical clock values for send, recieve and internal events for 3 processes

Both processToLC.cpp and LCtoProcess.cpp should be compiled and run separately.
Both files should be compiled with C++11.

processToLC.cpp: //takes events as input, outputs calculated logical clock valeus
	Modify pMatrix to change input.
	Initializes a 2 dimensional array with string values representing m columns of events at n rows of processes.
	
	pushClock() takes:
	the inputted string matrix,
	an empty matrix to store the logical clock values, 
	an array to keep track of send messages,
	and the number of receives that will need to be accounted for

	loop through every process:
		reset the logical clock value to 1
		loop through events of process:
			check event type
			if send then store clock value and wait for matching receive event
			if receive then check for matching send
				if matching send value, store logical clock value
				else move to next process
			else continue
	//eventually all of the sends and receives will be matched and the leftover internal operations can be ordered

	prints array of clock values

processToLC.out: 
	contains terminal output of the program using default example input

LCtoProcess.cpp: //takes clock values as input, validates them, and outputs the original events
	initalize inputted matrix of clock values
	check for validity of array based on consecutive clock values

	PushProcess() takes:
		empty string matrix to store events
		matrix of clock values
		highest clock value in matrix

		Does: finds the corresponding events and stores them into the empty string matrix
		Loops through the processes and events and stores all events as "internal"
		If non consecutive events are found, they are identified as receive messages.
			Call foundRecEvent()
	foundRecEvent() takes:
		matrix of clock values,
		empty string matrix of events,
		indexes of current found receive event,
		current highest clock value,
		current count of found send values
	
		Does: Finds matching send event and stores both into the empty matrix of events
		See if the highest clock value found so far is at least >= the receive message
		If it is not
			No send message found, exit the function
		If it is, find the corresponding indexes of clock value - 1
			Find the internal event in the process matrix, overwrite it as a send event
			Store the corresponding receive event in the process matrix
			Change the value of the highest clock count found
			Exit function
	changeInternals() takes:
		completed string matrix of events

		Does: fills in the letters for the leftover internal events starting at 'a'
		At this point, all events other than send and receive are marked with the same string, "internal"
		Over write all "internal" events with incremented characters

	for each event in each process:
		keep track of highest clock value seen
		ignore values for which the matching event has been filled
		if value is consecutive mark as internal/send
		else mark as receive and call foundRecEvent() which:
			finds the matching send event by searching for the clock value 
			immediately prior to the receive event
		call changeInternals() to mark all leftover internal/send events as
		internal and assign letters in order starting with 'a'


