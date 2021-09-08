
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


using namespace std;

#define NUM_THREADS 2

struct thread_data {
	int thread_id;
};
long searchStart[NUM_THREADS]; //Start Pos to read the file in each Thread
long outPos[30]; //Start Pos to write the file according to the first letter of the name 'A~Z'
int outCnt[30];

int threadCnt = 0; //The count of thread to be ended

time_t timerStart; // Start time of the project
sem_t semaforo;


void *ReadOrder(void *threadarg) { //Function assigned to each Thread
	struct thread_data *pData = (struct thread_data *)(threadarg);
	int id = pData->thread_id;
	ifstream inFile("input2.csv");
	ofstream outFile("result.txt");

	inFile.seekg(searchStart[id]); //move the pointer to the start position of each thread
	long curInPos, curOutPos;
	string tmpData;
	int letterId, letterPos;
	while ( getline(inFile, tmpData)) {
		letterPos = tmpData.find(','); //position of the first comma ( before name)
		letterId = (int)(tmpData[letterPos+1]-'A'); // get the id of the first character of the name: A-0, B-1... Z-25
		outFile.seekp ( outPos[letterId]); //move the pos of the the first letter of the name: (A~Z)

		sem_wait(&semaforo);
		outFile<<tmpData<<endl; // write file
		curOutPos = outFile.tellp();

		sem_post(&semaforo);
		cout<<curOutPos<<endl;

		outPos[letterId] = curOutPos; //update the last possition
		outCnt[letterId]++;
		curInPos = inFile.tellg();
		if ( id<NUM_THREADS-1 && curInPos>=searchStart[id+1]) break; //if read until the end of the content assigned to the thread
	}
	threadCnt++;
	if ( threadCnt ==NUM_THREADS ) { //If all the threads is ended, end the program
		ofstream indexFile("index.txt");
		for ( int i = 0; i<26; i++) {
			indexFile<<(char)(i+'A')<<","<<outCnt[i]<<endl;
		}
		time_t timerEnd;
		time(&timerEnd);
		cout<<timerEnd-timerStart<<"(s)"<<endl;
	}
   	pthread_exit(NULL);
}

int main () {

	sem_init(&semaforo,0,1);
	time(&timerStart); //get the time of starting the project
   	pthread_t threads[NUM_THREADS];
   	struct thread_data th[NUM_THREADS];

   	//outFile.open ("result.txt"); //open the output file

	ifstream inFile("input2.csv"); //open the input csv file
	long size; //size of the input file
	// start of getting the size of the input file
	inFile.seekg(0, ios::end);
	size = (long)(inFile.tellg());

	string tmpData;
	searchStart[0] = 0; //position of reading input csv file by the first thread
	th[0].thread_id = 0; //information of thread

	int i;
	for (i = 1; i<NUM_THREADS;i++) {
		searchStart[i] = (long)(size/NUM_THREADS*i); //position of reading input csv file by the i th thread
		th[i].thread_id = i; // information of i th thread
		inFile.seekg(searchStart[i]); //start of getting the exact position of i th thread
		getline(inFile, tmpData);
		searchStart[i] = inFile.tellg(); //end of getting the exact position of i th thread
	}
	for ( i = 0; i<26; i++) {
		outPos[i] = (long)(size/10*i); //position of output with the letter 'B C ... Z'
		outCnt[i] = 0;
	}
	inFile.close();
    int rc; //result of thread
    for(i = 0; i < NUM_THREADS; i++ ) {
        rc = pthread_create(&threads[i], NULL, ReadOrder, (void*)&th[i]); //creating the thread
        if (rc) {
	        cout << "Error:unable to create thread," << rc << endl;
	        exit(-1);
        }
    }
   pthread_exit(NULL);
}
