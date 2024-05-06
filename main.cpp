#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Cjd
{
public:
    int anzahlSchüler;
    float notenDurchschnitt;

    Cjd()
    {
        anzahlSchüler = 1000;
        notenDurchschnitt = 2.0;
    }

    Cjd(float *b)
    {
        anzahlSchüler = 1000;
        notenDurchschnitt = *b;
    }

    Cjd(int *a)
    {
        anzahlSchüler = *a;
        notenDurchschnitt = 2.0;
    }

    Cjd(int *a, float *b)
    {
        anzahlSchüler = *a;
        notenDurchschnitt = *b;
    }

    void fördern(int *anzahlFördergelder)
    {
        notenDurchschnitt -= (*anzahlFördergelder/(float)anzahlSchüler)/10000;
        if(notenDurchschnitt < 0.66)
        {
            notenDurchschnitt = 0.66;
        }
    }

    Cjd* welchegrößer (Cjd *a)
    {
        if(a->anzahlSchüler > this->anzahlSchüler)
        {
            return a;
        }
        return this;
    }
};

int fak(int *n)
{
    if(*n == 0)
    {
        return 0;
    }
    else if(*n == 1)
    {
        return 1;
    }
    else
    {
        int temp = *n - 1;
        return *n * fak(&temp);
    }
}

float sum(float *n, int size)
{
    float ret = 1;
    float *temp;
    for(int i = 0; i < size; i++)
    {
        temp = n + i;
        ret *= *temp;
    }
    return ret;
}

int main() {
    int a = 1400;
    int b = 2000;
    Cjd Königswinter(&a);
    Cjd *pKönigswinter = &Königswinter;
    Cjd LA(&b);
    Cjd *pLA = &LA;
    cout << (Königswinter.welchegrößer(pLA))->anzahlSchüler;
}