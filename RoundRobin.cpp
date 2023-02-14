#include <iostream>
#include <conio.h>
#include <queue>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
#define MAX 20
int i, NOP, sum = 0, count = 0, y, quant, WaitingTime = 0, UsingCPUTime = 0, at[MAX], bt[MAX], temp[MAX], bt2[MAX];
int check[MAX] = {-1};
int findProcessing(int timer) // tim tien trinh dang chay
{
    for (int i = 0; i < NOP; i++)
    {
        if (check[i] == 1) // 1 la dang chay
            return i;
    }
    return -1; // khong co tien trinh nao dang chay
}
int findProcessByTime(int timer) // tim tien trinh bat dau theo timer
{
    for (int i = 0; i < NOP; i++)
    {
        if (at[i] == timer) //
            return i;
    }
    return -1;
}
queue<int> QueueOfProcess;
void showQueue()
{
    queue<int> temp = QueueOfProcess;
    while (!temp.empty())
    {
        cout << " P" << temp.front() << "[" << bt[temp.front()] << "] ";
        temp.pop();
    }
}
int pushQueue(int timer)
{
    for (int i = 0; i < NOP; i++)
        if (at[i] == timer)
        {
            QueueOfProcess.push(i);
            return i;
        }
    return -1;
}
int checkisRunning(int timer)
{
    for (int i = 0; i < NOP; i++)
        if (check[i] == 1)
            return i;
    return -1;
}

int anyProcessRunning()
{
    int i, count = 0;
    for (i = 0; i < NOP; i++)
        if (check[i] == 2)
            count += 1;
    if (count == NOP)
        return 1; // da het tien trinh
    else
        return 0; // van con tien trinh
}
int main()
{
    // initlialize the variable name
    float avg_WaitingTime = 0, avg_UsingCPUTime = 0;
    int counter = 0;
    // Display the
    // int pid;
    int running;
    int processIn;

    // main
    int any = anyProcessRunning();



    // // read file
    // ifstream file("testcase.txt");
    // if(!file){printf("Make new file testcase.txt"); return 0;}
    // printf("Enter the Time Quantum for the process: ");
    // file >> quant;
    // cout << quant << endl;
    // printf("Total number of process in the system:  ");
    // file >> NOP;
    // cout << NOP << endl;
    // y = NOP;
    // for (i = 0; i < NOP; i++)
    // {
    //     printf("Enter Process[%d]\n", i);
    //     printf("   Arrival time is: \t"); // Accept arrival time
    //     file >> at[i];
    //     cout << at[i] << endl;
    //     printf("   Burst time is: \t"); // Accept the Burst time
    //     file >> bt[i];
    //     cout << bt[i] << endl;
    //     bt2[i] = bt[i]; // store the burst time in temp array
    // }



    // stdin
    // Accept the Time qunat
    printf("Enter the Time Quantum for the process: ");
    scanf("%d", &quant);

    printf("Total number of process in the system:  ");
    scanf("%d", &NOP);

    y = NOP; // Assign the number of process to variable y
    // Use for loop to enter the details of the process like Arrival time and the Burst Time
    for (i = 0; i < NOP; i++)
    {
        printf("Enter Process[%d]\n", i + 1);
        printf("   Arrival time is: \t"); // Accept arrival time
        scanf("%d", &at[i]);
        printf("   Burst time is: \t"); // Accept the Burst time
        scanf("%d", &bt[i]);
        bt2[i] = bt[i]; // store the burst time in temp array
    }



    printf("\nThere is getch() inside, so press enter to next step.\n\n");
    // Display the process No, burst time, Turn Around Time and the waiting time
    printf("|%5s | %7s |  %10s\t|  %6s\n", "Time", "Quantum", "Processing", "Queue");
    for (int timer = 0, counter = 0; timer < 100; timer++)
    {
        printf("|  %2d  ", timer);
        processIn = findProcessByTime(timer);
        running = checkisRunning(timer);
        if (processIn != -1) // co 1 tien trinh vao thoi diem timer
        {
            if (running != -1) // co tien trinh dang chay
            {

                QueueOfProcess.push(processIn);
            }
            else
                check[processIn] = 1;
        }
        if (timer != 0 && (counter) % quant == 0 && counter != 0)
        {
            running = checkisRunning(timer);
            check[running] = 0;
            QueueOfProcess.push(running);
            check[QueueOfProcess.front()] = 1;
            QueueOfProcess.pop();
            counter = 0;
        }
        {
            int processing = findProcessing(timer);
            if (processing != -1)
            {

                printf("|   %2d    |    P%d[%d]\t|", counter, processing, bt[processing]--);
                showQueue();

                if (bt[processing] == 0) // kiem tra ket thuc ?
                {
                    // printf("P%d finished !!", processing);
                    check[processing] = 2;        // danh dau la ket thuc
                    temp[processing] = timer + 1; // danh dau thoi gian ket thuc
                    counter = -1;

                    if (anyProcessRunning() == 0) // van con tien trinh
                    {
                        processing = QueueOfProcess.front();
                        // printf("P%d is going in !!", processing);

                        check[processing] = 1;
                        QueueOfProcess.pop();
                    }
                    else // da het tien trinh
                    {
                        printf("\n|  %2d  |   %2d    |    P%d[%d]\t|\n", timer + 1, counter + 1, running, bt[running]);
                        break;
                    }
                }
            }
        }
        counter++;
        cout << endl;
        // sleep_for(1000ms);
        getch();
    }
    // tinh toan thoi gian trung binh
    for (int i = 0; i < NOP; i++)
    {
        printf("Thoi gian ket thuc tien trinh %2d    : %d\n", i, temp[i]);
        WaitingTime = 1.0 * (temp[i] - at[i]);
        printf("Thoi gian luu lai tien trinh %2d     : %d\n", i, WaitingTime);
        UsingCPUTime += (WaitingTime - bt2[i]);
        printf("Thoi gian cho doi cua tien trinh %2d : %d\n\n", i, WaitingTime - bt2[i]);
    }
    // represents the average waiting time and Turn Around time
    avg_WaitingTime = WaitingTime * 1.0 / NOP;
    avg_UsingCPUTime = UsingCPUTime * 1.0 / NOP;
    // printf("\nTrung Binh Thoi Gian Luu Lai: \t%f", avg_WaitingTime);
    printf("\nThoi Gian Cho Doi Trung Binh cua %d tien trinh la: %2.3f", NOP, avg_UsingCPUTime);
    return 0;
}