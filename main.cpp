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

int main()
{
    bool run = true;

    do
    {
        cout << "Enter Command:";
        getline(cin, str);

        if(str == "Exit")
        {
            run = false;
        }

    } while (run);
}

void memoryManager (int memSize, int frameSize)
{

}

int allocate (int allocSize, int pid)
{

}

int deallocate (int pid)
{

}

int write (int pid, int logical_address)
{

}

int read (int pid, int logical_address)
{

}

void printMemory(void)
{

}