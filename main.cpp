#include <iostream>
#include "Dijkstra.h"

/**
 * You can use this file to test your code.
 */
int main()
{   
    DijkstraProject2 pro;
    freopen("input.txt", "r", stdin);
    while(pro.read)
    {pro.readFromFile();
    pro.run1();
    pro.run2();
    pro.reset();}
    fclose(stdin);
}
