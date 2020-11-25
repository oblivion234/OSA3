#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked.h"

using namespace std;

void memoryManager (int memSize, int frameSize);
int allocate (int allocSize, int pid);
int deallocate (int pid);
int write (int pid, int logical_address);
int read (int pid, int logical_address);
void printMemory(void);

int freeFrameList [100];
int freeFrameIndex = 0;
int processList [100][2];
int pageTable [100][2];
int *freeFrame;
int PTOffset = 0;
int pListOffset = 0;
list victims;

int main()
{
    bool run = true;
    int memSize, frameSize, sizeA, pid, addr1, ret;
    string str;

    for (int i = 0; i < 100; i++)
    {
        freeFrameList[i] = -1;
        pageTable[i][0] = -1;
        pageTable [i][1] = -1;
    }

    do
    {
        cout << "Enter Command:";
        cin >> str;

        if(str == "Exit")
        {
            run = false;
        }
        else
        {
            if(str[0] == 'M')
            {
                cin >> memSize;
                cin >> frameSize;
                memoryManager(memSize, frameSize);
            }
            else if (str[0] == 'A')
            {
                cin >> sizeA;
                cin >> pid;
                ret = allocate(sizeA, pid);
                if(ret==-1)
                {
                    cout<<"Error in allocation.\n";
                }
            }
            else if (str[0] == 'W')
            {
                cin >> pid;
                cin >> addr1;
                ret = write(pid, addr1);
                if(ret==-1)
                {
                    cout<<"No such page assigned to that process.\n";
                }
            }
            else if (str[0] == 'R')
            {
                cin >> pid;
                cin >> addr1;
                ret = read(pid, addr1);
                if(ret==-1)
                {
                    cout<<"No such page assigned to that process.\n";
                }
            }
            else if (str[0] == 'D')
            {
                cin >> pid;
                ret = deallocate(pid);
            }
            else if (str[0] == 'P')
            {
                printMemory();
            }
        }

    } while (run);
}

void memoryManager (int memSize, int frameSize)
{
    //creates freeframse of size passed by user
    freeFrame = new int [memSize];
    //sets all freeframes to 0 and sets the index of the frames in free frames list
    for (int i = 0; i < memSize; i++)
    {
        freeFrame[i] = 0;
        freeFrameList[freeFrameIndex] = i;
        freeFrameIndex++;
    }
}

int allocate (int allocSize, int pid)
{
    //cout << "ALLOC" << endl << allocSize << endl << pid<< endl;;
    srand(time(NULL));
    int randNum, runs, index,toDelete;
    bool notFound = true;
    bool error = false;
    randNum=rand()% freeFrameIndex;
    runs = 0;
    for(int i = 0;i<allocSize;i++)//For the full allocation
    {
        pageTable[i+PTOffset][0] = pid;//adds to the page table
        while(notFound)//searches for a random free frame
        {
            randNum=rand()% freeFrameIndex;
            if(freeFrameList[randNum]!=-1)
            {
                notFound = false;
                index  = freeFrameList[randNum];
                freeFrameList[randNum] = -1;
                victims.insertNode(index,pid);
            }
            runs++;
            if(runs>1000)//if there aren't any free frames
            {
                index=victims.searchList();
                toDelete=victims.returnPID(index);
                victims.deleteNode(index);
                victims.insertNode(index,pid);
               for(int j = 0;j<100;j++)
                {
                    if(pageTable[j][0]==toDelete&&pageTable[j][1]==index)
                        {

            pageTable[i][0]=-1;//clears page table
            pageTable[i][1]=-1;
        }
                }
                notFound=false;
            }
        }
        runs = 0;
        notFound = true;
        if(error)//stops if there is an error
        {
          return -1;
        }
        pageTable[i+PTOffset][1] = index;
    }
    PTOffset += allocSize;
    processList[pListOffset][0]=pid;
    processList[pListOffset][1]=allocSize;
    pListOffset++;
    return 1;
}

int deallocate (int pid)
{
    //cout << "DEALLOC" << endl << pid << endl;
    for(int i = 0;i<100;i++)//Goes through the page table
    {
        if(pageTable[i][0]==pid)
        {
            for(int j = 0;j<100;j++)
            {
                if(freeFrameList[j]==-1)//Finds the first available free frame
                {
                    freeFrameList[j]=pageTable[i][1];
                    j=1000;
                }
            }
            pageTable[i][0]=-1;//clears page table
            pageTable[i][1]=-1;
        }
    }
    return 1;
}

int write (int pid, int logical_address)
{
    //cout << "WRITE" <<  endl << pid << endl << logical_address << endl;
    int pageCount = 0;
    for(int i = 0;i<100;i++)//Finds the correct page
    {
        if(pageTable[i][0]==pid)
        {
            if(pageTable[i][0]==pid&&pageCount==logical_address)
            {
                freeFrame[pageTable[i][1]] = 1;//Writes to the correct page
                return 1;
            }
            pageCount++;
        }
    }
    return -1;
}

int read (int pid, int logical_address)
{
    //cout << "READ" <<  endl << pid << endl << logical_address << endl;
    int pageCount = 0;
    for(int i = 0;i<100;i++)//Finds correct page
    {
        if(pageTable[i][0]==pid)
        {
            if(pageTable[i][0]==pid&&pageCount==logical_address)
            {
                cout<<freeFrame[pageTable[i][1]]<<endl;//Prints contents
                return 1;
            }
            pageCount++;
        }
    }
    return -1;
}

void printMemory(void)
{
    //free
    //display free frames
    cout << "Free" << endl;
    for (int i = 0; i < 100; i ++)
    {
        if (freeFrameList[i] != -1)
        {
            cout << i << " ";
        }
    }
    cout << endl << endl;

    //process
    //display process size and pid
    cout << "Process" << endl;
    for (int i = 0; i < 100; i++)
    {
        if (processList[i][0] > 0)
        {
            cout << processList[i][0] << " ";
            cout << processList[i][1];
            cout << endl;
        }
    }
    cout << endl << endl;

}
