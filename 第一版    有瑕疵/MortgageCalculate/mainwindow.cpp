#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "mortgage.h"
#include <cmath>


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
    //  结果变量
    int ys, cs;
    double yuegong,dkze,lixi,hkze,mydj,shoufu=0.0;

    //计算变量
    double rate,total;

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
                ys=252;
                break;
        case 21:
                ys=264;
                break;
        case 22:
                ys=276;
                break;
        case 23:
                ys=288;
                break;
        case 24:
                ys=300;
                break;
        default :
                return;
        }

    dkfs = ui->comboBox->currentIndex();// 商贷   公积金   组合
    hkfs = ui->comboBox_5->currentIndex();//  本息   本金


    if(dkfs == 0 || dkfs == 1)   // 商贷   公积金
    {
        jsfs = ui->comboBox_2->currentIndex();
        switch (jsfs)
        {
        case 0: // 面积单价

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
            double area,danjia;
            area = ui->lineEdit_2->text().toDouble();
            danjia = ui->lineEdit->text().toDouble();
            //  double rate,total;
            if(dkfs == 0)
            {
                rate = ui->lineEdit_5->text().toDouble();
                total = area*danjia;
            }
            if(dkfs == 1)
            {
                rate = ui->lineEdit_5->text().toDouble();
                total = area*danjia;
            }
            if(hkfs == 0)  //  本息
            {
                dkze = total*cs/10;
                shoufu = total - dkze;
            }
            if(hkfs == 1)  //  本金
            {
                dkze = total*cs/10;
                shoufu = total - dkze;
            }

            break;
        case 1:     // 总额
            if(dkfs == 0)
            {
                total = ui->lineEdit_3->text().toDouble();
                rate = ui->lineEdit_5->text().toDouble();
            }
            if(dkfs == 1)
            {
                total = ui->lineEdit_4->text().toDouble();
                rate = ui->lineEdit_6->text().toDouble();
            }

            break;
        }
        if(hkfs == 0)  //  本息
        {
            yuegong = (dkze*rate/12/100*pow(1+rate/12/100,ys))/(pow(1+rate/12/100,ys)-1);
            hkze = yuegong*ys;
            lixi = hkze - dkze;

            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(shoufu,10,0)+"元\n");
            ui->textBrowser->append("每月月供： "+QString::number(yuegong,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
        }
        if(hkfs == 1)  //  本金
        {
            dkze = total;
            yuegong = total*rate/12/100 + total/ys;
            mydj = total * rate/12/100 * rate/12/100;
            lixi = dkze * rate/12/100 * (ys+1)/2;
            hkze = dkze + lixi;
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("    首付： "+QString::number(shoufu,10,0)+"元\n");
            ui->textBrowser->append("首月月供： "+QString::number(yuegong,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
        }
    }
    if(dkfs == 2)     //   组合贷款
    {
        //数据读入
        double grate,srate,gTotal,sTotal;
        grate = ui->lineEdit_6->text().toDouble();
        srate = ui->lineEdit_5->text().toDouble();
        gTotal = ui->lineEdit_4->text().toDouble();
        sTotal = ui->lineEdit_3->text().toDouble();

        if(hkfs == 0)
        {
            dkze = (sTotal+gTotal)*10000;
            yuegong = sTotal*(srate/12/100*pow(1+srate/12/100,ys))/(pow(1+srate/12/100,ys)-1)+gTotal*(grate/12/100*pow(1+grate/12/100,ys))/(pow(1+grate/12/100,ys)-1);
            hkze = yuegong*ys;
            lixi = hkze - dkze;

            // 输出
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("每月月供： "+QString::number(yuegong,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
        }
        if(hkfs == 1)
        {
            dkze = (sTotal+gTotal)*10000;
            yuegong = sTotal/ys+sTotal*srate/12/100 + gTotal/ys+gTotal*grate/12/100;
            double f1,f2;
            f1 = sTotal/ys+(sTotal-(sTotal/ys+sTotal*srate/12/100))*srate/12/100;
            f2 = gTotal/ys+(gTotal-(gTotal/ys+gTotal*grate/12/100))*grate/12/100;
            mydj = yuegong - f1 - f2;
            lixi = sTotal*srate/12/100*(ys+1)/2 + gTotal*grate/12/100*(ys+1)/2;
            hkze = dkze + lixi;

            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("首月月供： "+QString::number(yuegong,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
        }

    }

    //   输出


}
