#include<iostream>
using namespace std;

void lru(int f, int n, int a[]) {
    int fault = 0, pos;
    int frame[f];
    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        bool allocated = false;
        //cout << a[i] << "page:" << endl;
        for (int j = 0; j < f; j++)
        {
            //cout << frame[j] << "frame." << endl;
            if(frame[j] == a[i])
            {
                allocated = true;
                break;
            }
            else if(frame[j] == -1)
            {
                frame[j] = a[i];
                fault++;
                allocated = true;
                //cout << "Fault " << fault;
                break;
            }
        }
        if (allocated == false)
        {
            int pos = -1, farthest = i+1;
            for (int j = 0; j < f; j++)
            {
                int k;
                for (k = i - 1; k >= 0; k--)
                {
                    if (frame[j] == a[k])
                    {
                        if (k < farthest)
                        {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }
                if (k == i)
                {
                    frame[j] = a[i];
                }
            }
            if (pos == -1)
            {
                frame[0] = a[i];
            }
            else
            {
                frame[pos] = a[i];
            }
            fault++;
        }
    }
    cout << fault;
}

int main() {
    int f, n;
    //cout << "Enter n: ";
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cin >> f;
    lru(f, n, a);
    return 0;
}