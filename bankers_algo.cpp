#include<iostream>
using namespace std;

#define m 3

bool safety(int n, int avail[], int max[][m], int allocation[][m], int need[][m]) {
    int work[m], seq[n];
    bool finish[n];
    for (int i = 0; i < n; i ++)
    {
        finish[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    int c = 0;
    for (int k = 0; k < n; k++)
    {   
        bool f;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == false)
            {
                f = false;
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m)
                {
                    for (int z = 0; z < m; z++)
                    {
                        work[z] += allocation[i][z];
                    }
                    finish[i] = true;
                    seq[c] = i;
                    c++;
                    f = true;
                }
            }
        }
        if(f == false)
        {
            cout << "System is in unsafe state." << endl;
            return false;
        }
    }

    cout << "System is in safe state." << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << seq[i] << " ";
    }
    cout << endl;
    return true;
}

void request(int n, int avail[], int max[][m], int allocation[][m], int need[][m]) {
    int num;
    int req[m];
    cout << "Enter process number: ";
    cin >> num;
    cout << "Enter the request: ";
    for (int i = 0; i < m; i++)
    {
        cin >> req[i];
    }
    for (int i = 0; i < m; i++)
    {
        if (req[i] <= need[num][i])
        {
            if (req[i] <= avail[i])
            {
                avail[i] -= req[i];
                allocation[num][i] += req[i];
                need[num][i] -= req[i]; 
            }
        }
    }
    safety(n, avail, max, allocation, need);
}

int main() {
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;
    int avail[m];
    cout << "Enter available resources: ";
    for (int i = 0; i < m; i++)
    {
        cin >> avail[i];
    }
    int max[n][m], allocation[n][m], need[n][m];
    cout << "Enter max and allocation for each process: " << endl;
    for (int i = 0; i < n; i ++)
    {
        cout << "For process P" << i << ":" << endl;
        cout << "max: ";
        for (int j = 0; j < m; j++)
        {
            cin >> max[i][j];
        }
        cout << "allocation: ";
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    safety(n, avail, max, allocation, need);
    request(n, avail, max, allocation, need);
    return 0;
}