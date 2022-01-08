#include <bits/stdc++.h>
using namespace std;

void srtf(int p[], int bt[], int arrt[], int n) {
    int complete = 0, t = 0, min = INT_MAX;
    int shortest = 0, end;
    bool check = false;
    int swt, stat;
    int remt[n], wt[n], tat[n];
    for (int i = 0; i < n; i++)
    {
        remt[i] = bt[i];
    }

    while (complete != n) {
        for (int i = 0; i < n; i++)
        {
            if (arrt[i] <= t && remt[i] < min && remt[i] > 0)
            {
                min = remt[i];
                shortest = i;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }
        remt[shortest]--;
        min = remt[shortest];
        if (min == 0)
            min = INT_MAX;
        
        if (remt[shortest] == 0)
        {
            complete++;
            check = false;
            end = t+1;
            wt[shortest] = end - bt[shortest] - arrt[shortest];
            swt = wt[shortest] + end - bt[shortest] - arrt[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
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
    int bt[n], p[n], arrt[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = i+1;
    }
    cout << "Enter Burst times: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> bt[i];
    }
    cout << "Enter Arrival times: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arrt[i];
    }

    srtf(p, bt, arrt, n);
    return 0;
}
 