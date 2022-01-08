#include<iostream>
using namespace std;

void fcfs(int p[], int bt[], int n) {
    
    int swt = 0, stat = 0;
    int wt[n], tat[n];
    wt[0] = 0;
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

void fcfs (int p[], int bt[], int n, int arrt[]) {
    int swt = 0, stat = 0;
    int wt[n], tat[n], c[n];
    wt[0] = 0;
    c[0] = arrt[0];
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (arrt[i] > arrt[j])
            {
                int temp1 = arrt[i];
                arrt[i] = arrt[j];
                arrt[j] = temp1;

                int temp2 = bt[i];
                bt[i] = bt[j];
                bt[j] = temp2;

                int temp3 = p[i];
                p[i] = p[j];
                p[j] = temp3;
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        c[i] = c[i-1] + bt[i-1];
        wt[i] = c[i] - arrt[i];
        swt += wt[i];
    }
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        stat += tat[i];
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
        fcfs(p, bt, n);
    }
    else if (f == 2)
    {
        int arrt[n];
        cout << "Enter Arrival times: " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> arrt[i];
        }
        fcfs(p, bt, n, arrt);
    }
    else
    {
        cout << "Invalid option entered.";
    }
    return 0;
}