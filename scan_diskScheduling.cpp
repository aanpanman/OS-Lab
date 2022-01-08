#include <iostream>
#include <cmath>
using namespace std;

void scan(int head, int r, int requests[], int total)
{
    int seek = 0, pos;
    for (int i = 0; i < r; i++) // sorting disk locations
    {
        for (int j = i; j < r; j++)
        {
            if (requests[i] > requests[j])
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    for (int i = 0; i < r; i++) // to find loc of disc in array
    {
        if (head == requests[i])
        {
            pos = i;
            break;
        }
    }
    seek += abs(total - requests[pos]) + abs(total - requests[0]);
    cout << seek;
}

int main()
{
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
    int requests[r + 1];
    cout << "enter requests: ";
    for (int i = 0; i < r; i++)
    {
        cin >> requests[i];
    }
    requests[r] = curr_head;
    r++;
    scan(curr_head, r, requests, total-1);
    return 0;
}
