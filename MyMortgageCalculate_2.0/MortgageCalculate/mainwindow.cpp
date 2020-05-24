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

    ui->lineEdit->setPlaceholderText(tr("请输入房屋单价"));
    ui->lineEdit_2->setPlaceholderText(tr("请输入房屋面积"));
    ui->lineEdit_3->setPlaceholderText(tr("请输入商贷总额"));
    ui->lineEdit_4->setPlaceholderText(tr("请输入公积金贷款额"));
    ui->lineEdit_5->setPlaceholderText(tr("请输入商贷利率"));
    ui->lineEdit_6->setPlaceholderText(tr("请输入公积金利率"));
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
    //double yuegong,dkze,lixi,hkze,mydj,shoufu=0.0;
    mortgage cal;
    mortgage s,g,ans;

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
                rate = ui->lineEdit_6->text().toDouble();
                total = area*danjia;
            }
            if(hkfs == 0)  //  本息
            {
                cal.dkze = total*cs/10;
                cal.shoufu = total - cal.dkze;
            }
            if(hkfs == 1)  //  本金
            {
                cal.dkze = total*cs/10;
                cal.shoufu = total - cal.dkze;
            }

            break;
        case 1:     // 总额
            if(dkfs == 0)
            {
                total = ui->lineEdit_3->text().toDouble();
                cal.dkze = total * 10000;
                rate = ui->lineEdit_5->text().toDouble();
            }
            if(dkfs == 1)
            {
                total = ui->lineEdit_4->text().toDouble();
                cal.dkze = total * 10000;
                rate = ui->lineEdit_6->text().toDouble();
            }

            break;
        }
        if(hkfs == 0)  //  本息
        {
            cal.xi(rate,ys);

            //  输出结果
            ui->textBrowser->append("          计算结果\n");
            if(jsfs == 0)   //  根据贷款总额计算无需首付
                ui->textBrowser->append("    首付： "+QString::number(cal.shoufu,10,0)+"元\n");
            ui->textBrowser->append("每月月供： "+QString::number(cal.yuegong,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
        }
        if(hkfs == 1)  //  本金
        {
            cal.jin(rate,ys);

            //    输出结果
            ui->textBrowser->append("          计算结果\n");
            if(jsfs == 0)
                ui->textBrowser->append("    首付： "+QString::number(cal.shoufu,10,0)+"元\n");
            ui->textBrowser->append("首月月供： "+QString::number(cal.yuegong,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(cal.mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(cal.dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(cal.lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(cal.hkze,10,0)+"元\n");
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
        gTotal *= 10000;
        sTotal *= 10000;

        switch (hkfs)
        {
        case 0:

            s.dkze = sTotal;
            g.dkze = gTotal;
            s.xi(srate,ys);
            g.xi(grate,ys);
            ans = s + g;


            // 输出
            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("每月月供： "+QString::number(ans.yuegong,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(ans.dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(ans.lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(ans.hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");

            break;
        case 1:
            s.dkze = sTotal;
            g.dkze = gTotal;
            s.jin(srate,ys);
            g.jin(grate,ys);
            ans = s + g;

            ui->textBrowser->append("          计算结果\n");
            ui->textBrowser->append("首月月供： "+QString::number(ans.yuegong,10,0)+"元\n");
            ui->textBrowser->append("每月递减： "+QString::number(ans.mydj,10,0)+"元\n");
            ui->textBrowser->append("贷款总额： "+QString::number(ans.dkze,10,0)+"元\n");
            ui->textBrowser->append("支付利息： "+QString::number(ans.lixi,10,0)+"元\n");
            ui->textBrowser->append("还款总额： "+QString::number(ans.hkze,10,0)+"元\n");
            ui->textBrowser->append("还款月数： "+QString::number(ys,10,0)+"月\n");
            break;
        }

    }

    //   归零
    ys = 0;
    cs = 0;
    rate = 0.0;
    total = 0.0;
    cal.reset();
    s.reset();
    g.reset();
    ans.reset();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append("	      使用说明书\n");
    ui->textBrowser->append("若选择商业贷款或公积金贷款\n");
    ui->textBrowser->append("  请先选择贷款方式\n");
    ui->textBrowser->append("  1.根据面积、单价计算\n");
    ui->textBrowser->append("    输入房屋单价、房屋面积及对应的贷款利\n");
    ui->textBrowser->append("率，并选择按揭成数、按揭年数、还款方式\n");
    ui->textBrowser->append("  2.根据贷款总额\n");
    ui->textBrowser->append("    输入对应贷款总额、利率，并选择按揭年\n");
    ui->textBrowser->append("数，还款方式\n");
    ui->textBrowser->append("若选择组合型贷款\n");
    ui->textBrowser->append("  只需输入商贷贷款总额、公积金贷款总额及\n");
    ui->textBrowser->append("其对应的利率，再选择还款方式即可计算\n");

}
