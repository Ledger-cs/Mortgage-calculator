#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <cmath>
#include <QMessageBox>
#include "mycal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();


    int dkfs,jsfs,chengs,nians,hkfs;//链接下拉框
    mycalculate cal;// 创建对象

    int cs,ys;
    //  贷款月数转换   nians  ys
    nians = ui->comboBox_4->currentIndex();
    switch (nians)
    {
    case 0:
            ys=12;
            break;
        case 1:
            ys=24;
            break;
        case 2:
            ys=36;
            break;
        case 3:
            ys=48;
            break;
        case 4:
            ys=60;
            break;
        case 5:
            ys=72;
            break;
        case 6:
            ys=84;
            break;
        case 7:
            ys=96;
            break;
        case 8:
            ys=108;
            break;
        case 9:
            ys=120;
            break;
        case 10:
            ys=132;
            break;
        case 11:
            ys=144;
            break;
        case 12:
            ys=156;
            break;
        case 13:
            ys=168;
            break;
        case 14:
            ys=180;
            break;
        case 15:
            ys=192;
            break;
        case 16:
            ys=204;
            break;
        case 17:
            ys=216;
            break;
        case 18:
            ys=228;
            break;
        case 19:
            ys=240;
            break;
        case 20:
            ys=300;
            break;
        case 21:
            ys=360;
            break;
        default :
            return;
    }
    //按揭成数转换  chengs   cs
    chengs = ui->comboBox_3->currentIndex();
    switch (chengs)
    {
    case 0:
            cs=9;
            break;
        case 1:
            cs=8;
            break;
        case 2:
            cs=7;
            break;
        case 3:
            cs=6;
            break;
        case 7:
            cs=2;
            break;
        case 4:
            cs=5;
            break;
        case 5:
            cs=4;
            break;
        case 6:
            cs=3;
            break;
        default :
            return;
    }

    //运用switch嵌套调用计算
    //贷款类别为最外一层   接着为计算方式  最后为还款方式
    dkfs = ui->comboBox->currentIndex();
    jsfs = ui->comboBox_2->currentIndex();
    hkfs = ui->comboBox_5->currentIndex();
    switch (dkfs)
    {
    case 0:    //商业贷款计算
    {
        bool xi,jin;
        xi = jin = false;
        if(hkfs == 0)
            jin = true;
        else
            xi = true;

        switch (jsfs)
        {
        case 0:    //根据面积计算
        {
            cal.in_area = ui->lineEdit_6->text().toInt();
            cal.in_danjia = ui->lineEdit_5->text().toInt();
            cal.in_srate = ui->lineEdit_18->text().toInt();

            cal.in_sTotal = cal.in_area*cal.in_srate/10000;

            if(xi)            //等额本息还款
            {
                cal.out_dkze1 = cal.in_sTotal*cs/10;
                cal.out_sf1 = cal.in_sTotal - cal.out_dkze1;
            }
            else
                cal.out_dkze1 = cal.out_sf1 = 0.0;
            if(jin)          //等额本金还款
            {
                cal.out_dkze2 = cal.in_sTotal*cs/10;
                cal.out_sf2 = cal.in_sTotal - cal.out_dkze2;
            }
            else
                cal.out_dkze2 = cal.out_sf2 = 0.0;
            break;
        }
        case 1:   //根据贷款总额计算
        {
            cal.in_area = cal.in_danjia = 0;
            cal.in_sTotal = ui->lineEdit_11->text().toInt();

            if(xi)                    //等额本息还款
            {
                cal.out_dkze1 = cal.in_sTotal;
                cal.out_sf1 = 0;
            }
            else
                cal.out_dkze1 = cal.out_sf1 = 0.0;
            if(jin)          //等额本金还款
            {
                cal.out_dkze2 = cal.in_sTotal;
                cal.out_sf2 = 0;
            }
            else
                cal.out_dkze2 = cal.out_sf2 = 0.0;
            break;
        }
        }
        //bene  benjin js
        if(xi)
        {
            cal.out_yjhk1 = (cal.out_dkze1*cal.in_srate/12/100*pow(1+cal.in_srate/12/100,ys))/(pow(1+cal.in_srate/1200,ys)-1);
            cal.out_hkze1 = cal.out_yjhk1*ys;
            cal.out_lixi1 = cal.out_hkze1 - cal.out_dkze1;
            cal.out_dkys1 = ys;
            cal.out_fkze1 = cal.in_sTotal;
        }
        else
            cal.out_yjhk1 = cal.out_hkze1 = cal.out_lixi1 = cal.out_fkze1 = cal.out_dkys1 =0.0;
        if(jin)
        {
            cal.out_yjhk2 = cal.out_dkze2/ys+(cal.out_dkze2-0)*cal.in_srate/12/100;
            cal.out_mydj = (cal.out_yjhk2-(cal.out_dkze2/ys+(cal.out_dkze2-cal.out_yjhk2)*cal.in_srate/12/100))*10000;
            cal.out_lixi2 = cal.out_dkze2*cal.in_srate/12/100*(ys+1)/2;
            cal.out_hkze2 = cal.out_dkze2+cal.out_lixi2;
            cal.out_dkys2 = ys;
            cal.out_fkze2 = cal.in_sTotal;
        }
        else
            cal.out_yjhk2 = cal.out_mydj =cal.out_lixi2 =cal.out_hkze2 =cal.out_dkys2 =cal.out_fkze2 =0.0;
        break;
    }
    case 1:   //公积金贷款
    {
        bool xi,jin;
        xi = jin = false;
        if(hkfs == 0)
            jin = true;
        else
            xi = true;

        switch (jsfs)
        {
        case 0:
            cal.in_area = ui->lineEdit_6->text().toInt();
            cal.in_danjia = ui->lineEdit_5->text().toInt();
            cal.in_grate = ui->lineEdit_21->text().toInt();

            cal.in_gTotal = cal.in_area*cal.in_danjia/10000;

            if(xi)
            {
                cal.out_dkze1 = cal.in_gTotal*cs/10;
                cal.out_sf1 = cal.in_gTotal-cal.out_dkze1;
            }
            else
                cal.out_dkze1 = cal.out_sf1 = 0.0;
            if(jin)
            {
                cal.out_dkze2 = cal.in_gTotal*cs/10;
                cal.out_sf2 = cal.in_gTotal - cal.out_dkze2;
            }
            else
                cal.out_dkze2 =cal.out_sf2 =0.0;
            break;
        case 1:
            cal.in_area = cal.in_danjia = 0.0;
            cal.in_gTotal = ui->lineEdit_12->text().toInt();

            if(xi)
            {
                cal.out_dkze1=cal.in_gTotal;
                cal.out_sf1 = 0.0;
            }
            else
                cal.out_dkze1=cal.out_sf1 = 0.0;
            if(jin)
            {
                cal.out_dkze2 = cal.in_gTotal;
                cal.out_sf2 = 0.0;
            }
            else
                cal.out_dkze2 = cal.out_sf2 = 0.0;

            break;
        }
        if(xi)
        {
            cal.out_yjhk1 = (cal.out_dkze1*cal.in_grate/12/100*pow(1+cal.in_grate/12/100,ys))/(pow(1+cal.in_grate/1200,ys)-1);
            cal.out_hkze1 = cal.out_yjhk1*ys;
            cal.out_lixi1 = cal.out_hkze1 - cal.out_dkze1;
            cal.out_dkys1 = ys;
            cal.out_fkze1 = cal.in_gTotal;
        }
        else
            cal.out_yjhk1 = cal.out_hkze1 = cal.out_lixi1 = cal.out_fkze1 = cal.out_dkys1 =0.0;
        if(jin)
        {
            cal.out_yjhk2 = cal.out_dkze2/ys+(cal.out_dkze2-0)*cal.in_grate/12/100;
            cal.out_mydj = (cal.out_yjhk2-(cal.out_dkze2/ys+(cal.out_dkze2-cal.out_yjhk2)*cal.in_grate/12/100))*10000;
            cal.out_lixi2 = cal.out_dkze2*cal.in_grate/12/100*(ys+1)/2;
            cal.out_hkze2 = cal.out_dkze2+cal.out_lixi2;
            cal.out_dkys2 = ys;
            cal.out_fkze2 = cal.in_gTotal;
        }
        else
            cal.out_yjhk2 = cal.out_mydj =cal.out_lixi2 =cal.out_hkze2 =cal.out_dkys2 =cal.out_fkze2 =0.0;

        break;
    }
    case 2:       //组合型贷款
        //数据读入
        cal.in_grate = ui->lineEdit_21->text().toInt();
        cal.in_srate = ui->lineEdit_18->text().toInt();
        cal.in_gTotal = ui->lineEdit_12->text().toInt();
        cal.in_sTotal = ui->lineEdit_11->text().toInt();

        bool xi,jin;
        xi = jin = false;
        if(hkfs == 0)
            jin = true;
        else
            xi = true;

        if(xi)
        {
            cal.out_dkze1 = cal.in_sTotal+cal.in_gTotal;
            cal.out_sf1 = 0.0;
            cal.out_fkze1=cal.out_dkze1;
            cal.out_dkys1=ys;
            cal.out_yjhk1=(cal.in_sTotal*cal.in_srate/12/100*pow(1+cal.in_srate/12/100,ys))/(pow(1+cal.in_srate/12/100,ys)-1)+(cal.in_gTotal*cal.in_grate/12/100*pow(1+cal.in_grate/12/100,ys))/(pow(1+cal.in_grate/12/100,ys)-1);
            cal.out_hkze1 = cal.out_yjhk1*ys;
            cal.out_lixi1=cal.out_hkze1-cal.out_dkze1;
        }
        else
            cal.out_dkze1 =cal.out_sf1 =cal.out_fkze1=cal.out_dkys1=cal.out_yjhk1=cal.out_hkze1 =cal.out_lixi1=0.0;
        if(jin)
        {
            cal.out_dkze2 = cal.in_sTotal+cal.in_gTotal;
            cal.out_sf2 = 0.0;
            cal.out_fkze2=cal.out_dkze2;
            cal.out_dkys2=ys;
            cal.out_yjhk2 = cal.in_sTotal/ys+(cal.in_sTotal-0)*cal.in_srate/12/100 + cal.in_gTotal/ys+(cal.in_gTotal-0)*cal.in_grate/12/100;
            double f1,f2;
            f1 = cal.in_sTotal/ys+(cal.in_sTotal-(cal.in_sTotal/ys+(cal.in_sTotal-0)*cal.in_srate/12/100))*cal.in_srate/12/100;
            f2 = cal.in_gTotal/ys+(cal.in_gTotal-(cal.in_gTotal/ys+(cal.in_gTotal-0)*cal.in_grate/12/100))*cal.in_grate/12/100;
            cal.out_mydj = (cal.out_yjhk2-f1-f2)*10000;
            cal.out_lixi2 = cal.in_sTotal*cal.in_srate/12/100*(ys+1)/2 + cal.in_gTotal*cal.in_grate/12/100*(ys+1)/2;
            cal.out_hkze2 = cal.out_dkze2+cal.out_lixi2;
        }
        else
            cal.out_dkze2 =cal.out_sf2 =cal.out_fkze2=cal.out_yjhk2 =cal.out_mydj =cal.out_lixi2 =cal.out_hkze2 =0.0;

        break;
    default:
        return;
    }

    //   输出
    switch (dkfs)
    {
    case 0:
        switch (hkfs)
        {
        case 0:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(cal.out_sf1,10,0)+"元\n");
            ui->textBrowser->append("首月月供： "+QString::number(cal.out_yjhk2,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(cal.out_mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze2,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi2,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze2,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys2,10,0)+"月\n");
            break;
        case 1:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(cal.out_sf1,10,0)+"元\n");
            ui->textBrowser->append("每月月供： "+QString::number(cal.out_yjhk1,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze1,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi1,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze1,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys1,10,0)+"月\n");
            break;
        }
        break;
    case 1:
        switch (hkfs)
        {
        case 0:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(cal.out_sf1,10,0)+"元\n");
            ui->textBrowser->append("首月月供： "+QString::number(cal.out_yjhk2,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(cal.out_mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze2,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi2,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze2,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys2,10,0)+"月\n");
            break;
        case 1:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(cal.out_sf1,10,0)+"元\n");
            ui->textBrowser->append("每月月供： "+QString::number(cal.out_yjhk1,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze1,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi1,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze1,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys1,10,0)+"月\n");
            break;
        }
        break;
    case 2:
        switch (hkfs)
        {
        case 0:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("首月月供： "+QString::number(cal.out_yjhk2,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(cal.out_mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze2,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi2,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze2,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys2,10,0)+"月\n");
            break;
        case 1:
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("每月月供： "+QString::number(cal.out_yjhk1,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.out_fkze1,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.out_lixi1,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.out_hkze1,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(cal.out_dkys1,10,0)+"月\n");
            break;
        }
        break;
    }

}

void MainWindow::on_pushButton_2_clicked()
{

}
