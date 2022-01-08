#include<iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter the number of processes: " << endl;
    cin >> n;
    cout << "Enter the number of resource types: " << endl;
    cin >> m;
    
    int available[m];
    cout << "Enter available vector: " << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
    }
    
    int allocation[n][m], max[n][m], needs[n][m];
    cout << "Enter the allocation matrix: " << endl;
    for (int i = 0; i < n; i ++)
    {
        cout << "Allocation for process " << i+1 << endl;
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }
    
    for (int i = 0; i < n; i ++)
    {
        cout << "Max for process " << i+1 << endl;
        for (int j = 0; j < m; j++)
        {
            cin >> max[i][j];
        }
    }

    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j++)
        {
            needs[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    int num;
    cout << "Which Process has request " << endl;
    cin >> num;
    int request[m];
    cout << "Request Vector " << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> request[i];
    }
    
    for (int i = 0; i < m; i++)
    {
        if (request[i] <= needs[num-1][i])
        {
            if (request[i] <= available[i])
            {
                available[i] -= request[i];
                allocation[num-1][i] += request[i];
                needs[num-1][i] -= request[i]; 
            }
        }
    }
    
    int work[m], sequence[n];
    bool finish[n];
    for (int i = 0; i < n; i ++)
    {
        finish[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
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
                    if (needs[i][j] > work[j])
                        break;
                }
                if (j == m)
                {
                    for (int z = 0; z < m; z++)
                    {
                        work[z] += allocation[i][z];
                    }
                    finish[i] = true;
                    sequence[c] = i;
                    c++;
                    f = true;
                }
            }
        }
        if(f == false)
        {
            cout << "No" << endl;
            break;
        }
    }

    cout << "Yes" << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << sequence[i] << " ";
    }
    cout << endl;
    
    return 0;
}