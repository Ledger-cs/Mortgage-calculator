#ifndef MORTGAGE_H
#define MORTGAGE_H


class mortgage
{
public:
    double mydj,yuegong,dkze,lixi,hkze,shoufu;

    mortgage();
    void xi(double rate,int ys);
    void jin(double rate,int ys);
    mortgage operator+(const mortgage &R)
    {
        mortgage r;
        r.yuegong = yuegong + R.yuegong;
        r.dkze = dkze + R.dkze;
        r.lixi = lixi + R.lixi;
        r.hkze = hkze + R.hkze;
        r.mydj = mydj + R.mydj;

        return r;
    }
    void reset();
};

#endif // MORTGAGE_H
