#include "mortgage.h"
#include <cmath>

mortgage::mortgage()
{

}

void mortgage::xi(double rate,int ys)
{
    yuegong = (dkze*rate/12/100*pow(1+rate/12/100,ys))/(pow(1+rate/12/100,ys)-1);
    hkze = yuegong*ys;
    lixi = hkze - dkze;
}

void mortgage::jin(double rate,int ys)
{
    yuegong = dkze*rate/12/100 + dkze/ys;
    mydj = dkze/ys*rate/12/100;
    lixi = dkze * rate/12/100 * (ys+1)/2;
    hkze = dkze + lixi;
}

void mortgage::reset()
{
    yuegong = 0.0;
    mydj = 0.0;
    lixi = 0.0;
    hkze = 0.0;
    dkze = 0.0;
    shoufu = 0.0;
}
