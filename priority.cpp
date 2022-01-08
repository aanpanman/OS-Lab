#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void priority(int p[], int bt[], int n, int pr[]) {
    int swt = 0, stat = 0;
    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (pr[i] > pr[j])
            {
                int temp1 = pr[i];
                pr[i] = pr[j];
                pr[j] = temp1;

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

    cout << "Process order\t| Burst time\t| Priority\t| Waiting time\t| Turnaround time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout <<"P"<<p[i]<<"\t\t| "<<bt[i]<<"\t\t| "<<pr[i]<<"\t\t| "<<wt[i]<<"\t\t| "<<tat[i]<< endl; 
    }
    
    cout << "Average waiting time: " << avgwt << endl;
    cout << "Average turnaround time: " << avgtat << endl;
}

void priority(int p[], int bt[], int n, int pr[], int arrt[]) {
    
    int is_completed[n], startt[n], completiont[n], wt[n], tat[n];
    int swt = 0, stat = 0;
    memset(is_completed,0,sizeof(is_completed));
    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) 
        {
            if(arrt[i] <= current_time && is_completed[i] == 0) 
            {
                if(pr[i] > mx) 
                {
                    mx = pr[i];
                    idx = i;
                }
                if(pr[i] == mx) 
                {
                    if(arrt[i] < arrt[idx]) 
                    {
                        mx = pr[i];
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) 
        {
            startt[idx] = current_time;
            completiont[idx] = startt[idx] + bt[idx];
            tat[idx] = completiont[idx] - arrt[idx];
            wt[idx] = tat[idx] - bt[idx];
            
            stat += tat[idx];
            swt += wt[idx];

            is_completed[idx] = 1;
            completed++;
            current_time = completiont[idx];
            prev = current_time;
        }
        else 
        {
            current_time++;
        }
        
    }

    float avgwt = (float)swt/(float)n;
    float avgtat = (float)stat/(float)n;

    cout << "Process order\t| Burst time\t| Priority\t| Arrival time\t| Waiting time\t| Turnaround time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout <<"P"<<p[i]<<"\t\t| "<<bt[i]<<"\t\t| "<<pr[i]<<"\t\t| "<<arrt[i]<<"\t\t| "<<wt[i]<<"\t\t| "<<tat[i]<< endl; 
    }
    
    cout << "Average waiting time: " << avgwt << endl;
    cout << "Average turnaround time: " << avgtat << endl;
}


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int bt[n], p[n], pr[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = i+1;
    }
    cout << "Enter Burst times: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> bt[i];
    }
    cout << "Enter Priority: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> pr[i];
    }

    int f;
    cout << "Enter 1 for same arrival time/ 2 for different arrival time: ";
    cin >> f;
    if (f == 1)
    {
        priority(p, bt, n, pr);
    }
    else if (f == 2)
    {
        int arrt[n];
        cout << "Enter Arrival times: " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> arrt[i];
        }
        priority(p, bt, n, pr, arrt);
    }
    else
    {
        cout << "Invalid option entered.";
    }
    return 0;
}