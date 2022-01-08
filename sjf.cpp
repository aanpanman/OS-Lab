#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void sjf(int p[], int bt[], int n) {
    int swt = 0, stat = 0;
    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                int temp1 = bt[i];
                bt[i] = bt[j];
                bt[j] = temp1;

                int temp2 = p[i];
                p[i] = p[j];
                p[j] = temp2;
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
        swt += wt[i];
    }
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        stat += tat[i];
    }
    float avgwt = (float)swt/(float)n;
    float avgtat = (float)stat/(float)n;

    cout << "Process order\t| Burst time\t| Waiting time\t| Turnaround time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout <<"P"<<p[i]<<"\t\t| "<<bt[i]<<"\t\t| "<<wt[i]<<"\t\t| "<<tat[i]<< endl; 
    }
    
    cout << "Average waiting time: " << avgwt << endl;
    cout << "Average turnaround time: " << avgtat << endl;
}

void sjf(int p[], int bt[], int n, int arrt[]) {
    int is_completed[n], start_time[n], completion_time[n], tat[n], wt[n];
    memset(is_completed, 0, sizeof(is_completed));
    int completed = 0;
    int current_time = 0;
    int prev = 0;
    int swt = 0, stat = 0;

    while (completed != n){
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) 
        {
            if(arrt[i] <= current_time && is_completed[i] == 0) 
            {
                if(bt[i] < mn) 
                {
                    mn = bt[i];
                    idx = i;
                }
                if(bt[i] == mn) 
                {
                    if(arrt[i] < arrt[idx]) 
                    {
                        mn = bt[i];
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) 
        {
            start_time[idx] = current_time;
            completion_time[idx] = start_time[idx] + bt[idx];
            wt[idx] = start_time[idx] - arrt[idx];
            tat[idx] = bt[idx] + wt[idx];
            swt += wt[idx];
            stat += tat[idx];

            is_completed[idx] = 1;
            completed++;
            current_time = completion_time[idx];
            prev = current_time;
        }
        else 
        {
            current_time++;
        }
        
    }
    float avgwt = (float)swt/(float)n;
    float avgtat = (float)stat/(float)n;

    cout << "Process order\t| Burst time\t| Arrival time\t| Waiting time\t| Turnaround time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout <<"P"<<p[i]<<"\t\t| "<<bt[i]<<"\t\t| "<<arrt[i]<<"\t\t| "<<wt[i]<<"\t\t| "<<tat[i]<< endl; 
    }
    
    cout << "Average waiting time: " << avgwt << endl;
    cout << "Average turnaround time: " << avgtat << endl;

}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int bt[n], p[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = i+1;
    }
    cout << "Enter Burst times: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> bt[i];
    }

    int f;
    cout << "Enter 1 for same arrival time/ 2 for different arrival time: ";
    cin >> f;
    if (f == 1)
    {
        sjf(p, bt, n);
    }
    else if (f == 2)
    {
        int arrt[n];
        cout << "Enter Arrival times: " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> arrt[i];
        }
        sjf(p, bt, n, arrt);
    }
    else
    {
        cout << "Invalid option entered.";
    }
    return 0;
}