#ifndef MORTGAGE_H
#define MORTGAGE_H


class mortgage
{
public:
    double in_danjia,in_area,in_sTotal,in_gTotal,in_srate,in_grate;
    double out_fkze1,out_dkze1,out_hkze1,out_lixi1,out_sf1,out_dkys1,out_yjhk1;//本息
    double out_fkze2,out_dkze2,out_hkze2,out_lixi2,out_sf2,out_dkys2,out_yjhk2;//本金
    double out_mydj;
    mortgage();
};

#endif // MORTGAGE_H
