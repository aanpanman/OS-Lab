#include<iostream>
#include<cmath>
using namespace std;

void fcfs(int head, int r, int requests[]) {
    int seek = 0, pos = head;
    for (int i = 0; i < r; i++)
    {
        seek += abs(requests[i] - pos);
        pos = requests[i];
    }
    cout << seek;
}

int main() {
    int total, curr_head, r, requests[r];
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
    cout << "enter requests: ";
    for (int i = 0; i < r; i++)
    {
        cin >> requests[i];
    }

    fcfs(curr_head, r, requests);
    return 0;
}
