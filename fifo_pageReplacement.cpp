//Avantika Suryawanshi, 20BCE2051
#include <iostream>
using namespace std;

void fifo(int f, int n, int a[]) {
    int fault = 0; //initializing the no.of faults to be zero
    int frame[n]; 
    for (int i = 0; i < n; i++)
    {
        frame[i] = -1; //initialize each frame to -1 as a dummy value
    }
    int idx = 0; //starting index of the 1st frame
    for (int i = 0; i < n; i++) //iterate through the reference string
    {
        int flag = 0;
        for (int j = 0; j < f; j++)
        {
            if (a[i] == frame[j]) //check if the page is a hit or miss
            {
                flag = 1;
                break; //if page hits then break from loop
            }
        }
        if (flag == 0) //if page miss
        {
            idx = (idx + 1) % f; //modulo increment the index
            frame[idx] = a[i]; //replace the page
            fault++; //increment the no.of faults
        }
    }
    cout << "Page Faults" << endl << fault;
}

int main()
{
    int n, f; //getting frame size, length of reference string and the string
    cout << "Size of frame" << endl;
    cin >> f;
    cout << "Length of the refernce string" << endl;
    cin >> n;
    int a[n];
    cout << "Reference string" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    fifo(f, n, a);
    return 0;
}


            