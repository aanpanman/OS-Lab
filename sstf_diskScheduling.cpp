#include<iostream>
#include<cmath>
using namespace std;

void sstf(int head, int r, int requests[]) {
    int seek = 0, pos = head, dis[r];
    for (int i = 0; i < r; i++)
    {
        dis[i] = abs(head - requests[i]);
    }
    for (int i = 0; i < r-1; i++)
    {
        for (int j = i+1; j < r; j++)
        {
            if (dis[i] > dis[j])
            {
                int temp1 = dis[i];
                dis[i] = dis[j];
                dis[j] = temp1;

                int temp2 = requests[i];
                requests[i] = requests[j];
                requests[j] = temp2;
            }
        }
    }
    for (int i = 0; i < r; i++)
    {
        seek += abs(requests[i] - pos);
        pos = requests[i];
    }
    cout << seek;
}

int main() {
    int total, curr_head, r;
    cout << "total cylinders: ";
    cin >> total;
    cout << "curr head pos: ";
    cin >> curr_head;
    if (curr_head > total)
    {
        cout << "head pos > total.";
        return 1;
    }
    cout << "no of request: ";
    cin >> r;
    int requests[r];
    cout << "enter requests: ";
    for (int i = 0; i < r; i++)
    {
        cin >> requests[i];
    }

    sstf(curr_head, r, requests);
    return 0;
}
