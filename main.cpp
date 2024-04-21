#include <iostream>
using namespace std;
#include "Array.h"

int main()
{
//    int* dArray = new int[4];
//    for (int i = 0; i < 4; i++)
//    {
//        dArray[i] = rand() % 10;
//        cout << dArray[i] << " ";
//    }
//    cout << endl;


    Array<int> array;
    array.setSize(2,3);
    for (int i = 0; i < 4; i++)
    {
        array.add(rand() % 10);
    }
    array.add(1);
//    array.insertAt(4, 3);
    array.show();
//    array.insertAt(dArray, 4, 3);
    array.removeAt(2);
    array.show();


    return 0;
}