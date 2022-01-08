#include<iostream>
using namespace std;

void rr(int p[], int bt[], int n, int q) {
    int swt = 0, stat = 0;
    int rem_bt[n], wt[n], tat[n];
    for (int i = 0 ; i < n ; i++)
    {
        rem_bt[i] = bt[i];
    }
    int t = 0;

    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
                if (rem_bt[i] > q)
                {
                    t += q;
                    rem_bt[i] -= q;
                }
                else
                {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    swt += wt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
        break;
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

void rr(int p[], int bt[], int n, int q, int arrt[]) {
    int swt = 0, stat = 0, rem = n, check = 0, t, i;
    int rem_bt[n], wt[n], tat[n];
    for (int i = 0 ; i < n ; i++)
    {
        rem_bt[i] = bt[i];
    }
    
    for (t = 0, i = 0; rem != 0;)
    {
        if (rem_bt[i] <= q && rem_bt[i] > 0)
        {
            t += rem_bt[i];
            rem_bt[i] = 0;
            check = 1;
        }
        else if (rem_bt[i] > 0)
        {
            rem_bt[i] -= q;
            t += q;
        }

        if (rem_bt[i] == 0 && check == 1)
        {
            rem--;

            wt[i] = t - arrt[i] - bt[i];
            tat[i] = t - arrt[i];
            check = 0;
            
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (arrt[i+1] <= t)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        swt += wt[i];
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
    int n, q;
    cout << "Enter quantum: ";
    cin >> q;
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
        rr(p, bt, n, q);
    }
    else if (f == 2)
    {
        int arrt[n];
        cout << "Enter Arrival times: " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> arrt[i];
        }
        rr(p, bt, n, q, arrt);
    }
    else
    {
        cout << "Invalid option entered.";
    }
    return 0;
}