#include <iostream>
#include <string>
#include <cstring>

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

int main()
{
    bool run = true;
    int memSize, frameSize, size, pid, addr1, ret;
    string str;

    for (int i = 0; i < 100; i++)
    {
        freeFrameList[i] = -1;
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
                cin >> size;
                cin >> pid;
                ret = allocate(size, pid);
            }
            else if (str[0] == 'W')
            {
                cin >> pid;
                cin >> addr1;
                ret = write(pid, addr1);
            }
            else if (str[0] == 'R')
            {
                cin >> pid;
                cin >> addr1;
                ret = read(pid, addr1);
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
    //cout << "MEM" << endl << memSize << endl << frameSize << endl;
    int *freeFrame;
    freeFrame = new int [memSize];

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
}

int deallocate (int pid)
{
    //cout << "DEALLOC" << endl << pid << endl;
}

int write (int pid, int logical_address)
{
    //cout << "WRITE" <<  endl << pid << endl << logical_address << endl;
}

int read (int pid, int logical_address)
{
    //cout << "READ" <<  endl << pid << endl << logical_address << endl;
}

void printMemory(void)
{
    //free
    for (int i = 0; i < 100; i ++)
    {
        if (freeFrameList[i] != -1)
        {
            cout << i << " ";
            cout << freeFrameList[i] << endl;
        }
    }
    cout << endl << endl;
    //not free
        for (int i = 0; i < 100; i ++)
    {
        if (freeFrameList[i] == -1)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}