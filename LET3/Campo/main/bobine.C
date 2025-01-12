#include <cmath>
#include "DataReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "Integrator.h"
#include "TGraph2D.h"
#include "TF2.h"

int main(){
    DataReader Calib("data/calib.txt");
    DataReader Bobinezz("data/bobine-zz.txt");
    DataReader Bobinezx("data/bobine-zx.txt");
    DataReader Bobinexx("data/bobine-xx.txt");
    DataReader Helmholtzzz("data/helmholtz-zz.txt");
    DataReader Helmholtzzx("data/helmholtz-zx.txt");
    DataReader Helmholtzxx("data/helmholtz-xx.txt");
    DataReader ar("data/ar.txt");
    DataReader ferro("data/ferro.txt");

    vector<vector<double>> datac;
    vector<vector<double>> databzz;
    vector<vector<double>> databzx;
    vector<vector<double>> databxx;
    vector<vector<double>> datahzz;
    vector<vector<double>> datahzx;
    vector<vector<double>> datahxx;
    vector<vector<double>> dataa;
    vector<vector<double>> dataf;

    vector<double> temp;

    for(int i=0;i<Calib.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Calib.GetData()[i][j][0])));
        }
        datac.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinezz.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinezz.GetData()[i][j][0])));
        }
        databzz.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinezx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinezx.GetData()[i][j][0])));
        }
        databzx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinexx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinexx.GetData()[i][j][0])));
        }
        databxx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzzz.GetData()[i][j][0])));
        }
        datahzz.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzzx.GetData()[i][j][0])));
        }
        datahzx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzxx.GetData()[i][j][0])));
        }
        datahxx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<ar.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(ar.GetData()[i][j][0])));
        }
        dataa.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<ferro.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(ferro.GetData()[i][j][0])));
        }
        dataf.push_back(temp);
        temp.clear();
    }

    TGraph Gcalib; Gcalib.SetTitle(""); Gcalib.SetLineColor(kMagenta); Gcalib.SetLineWidth(3); Gcalib.SetMarkerStyle(16); Gcalib.SetMarkerColor(kAzure+3); Gcalib.SetMarkerSize(2);
    TGraph Gbzz;   Gbzz.SetTitle("");   Gbzz.SetLineColor(kMagenta);   Gbzz.SetLineWidth(3);   Gbzz.SetMarkerStyle(16);   Gbzz.SetMarkerColor(kViolet+2);   Gbzz.SetMarkerSize(2);
    TGraph Gbzx;   Gbzx.SetTitle("");   Gbzx.SetLineColor(kMagenta);   Gbzx.SetLineWidth(3);   Gbzx.SetMarkerStyle(16);   Gbzx.SetMarkerColor(kViolet+2);   Gbzx.SetMarkerSize(2);
    TGraph Gbxx;   Gbxx.SetTitle("");   Gbxx.SetLineColor(kMagenta);   Gbxx.SetLineWidth(3);   Gbxx.SetMarkerStyle(16);   Gbxx.SetMarkerColor(kViolet+2);   Gbxx.SetMarkerSize(2);
    TGraph Ghzz;   Ghzz.SetTitle("");   Ghzz.SetLineColor(kMagenta);   Ghzz.SetLineWidth(3);   Ghzz.SetMarkerStyle(16);   Ghzz.SetMarkerColor(kOrange-3);   Ghzz.SetMarkerSize(2);
    TGraph Ghzx;   Ghzx.SetTitle("");   Ghzx.SetLineColor(kMagenta);   Ghzx.SetLineWidth(3);   Ghzx.SetMarkerStyle(16);   Ghzx.SetMarkerColor(kOrange-3);   Ghzx.SetMarkerSize(2);
    TGraph Ghxx;   Ghxx.SetTitle("");   Ghxx.SetLineColor(kMagenta);   Ghxx.SetLineWidth(3);   Ghxx.SetMarkerStyle(16);   Ghxx.SetMarkerColor(kOrange-3);   Ghxx.SetMarkerSize(2);
    TGraph Gar;    Gar.SetTitle("");    Gar.SetLineColor(kMagenta);    Gar.SetLineWidth(3);    Gar.SetMarkerStyle(16);    Gar.SetMarkerColor(kAzure+3);    Gar.SetMarkerSize(2);
    TGraph Gfe;    Gar.SetTitle("");    Gfe.SetLineColor(kMagenta);    Gfe.SetLineWidth(3);    Gfe.SetMarkerStyle(16);    Gfe.SetMarkerColor(kAzure+3);    Gfe.SetMarkerSize(2);
    TGraph Gxb;    Gxb.SetTitle("");    Gxb.SetLineColor(kMagenta);    Gxb.SetLineWidth(3);    Gxb.SetMarkerStyle(16);    Gxb.SetMarkerColor(kAzure+3);    Gxb.SetMarkerSize(2);
    TGraph Gxh;    Gxh.SetTitle("");    Gxh.SetLineColor(kMagenta);    Gxh.SetLineWidth(3);    Gxh.SetMarkerStyle(16);    Gxh.SetMarkerColor(kAzure+3);    Gxh.SetMarkerSize(2);
    TGraph2D Gtotb;    Gtotb.SetTitle("");    Gtotb.SetLineColor(kMagenta);    Gtotb.SetLineWidth(3);    Gtotb.SetMarkerStyle(16);    Gtotb.SetMarkerColor(kAzure+3);    Gtotb.SetMarkerSize(2);
    TGraph2D Gtoth;    Gtoth.SetTitle("");    Gtoth.SetLineColor(kMagenta);    Gtoth.SetLineWidth(3);    Gtoth.SetMarkerStyle(16);    Gtoth.SetMarkerColor(kAzure+3);    Gtoth.SetMarkerSize(2);
    TGraph2D GInvis; GInvis.SetTitle("");
    TGraph GInvis2; GInvis2.SetTitle("");
    {
        TAxis *ax1 = Gcalib.GetXaxis();
        TAxis *ay1 = Gcalib.GetYaxis();
        ax1->SetTitle("I (A)");
        ay1->SetTitle("V (T)");
        TAxis *ax2 = Gbzz.GetXaxis();
        TAxis *ay2 = Gbzz.GetYaxis();
        ax2->SetTitle("z (m)");
        ay2->SetTitle("Bz (T)");
        TAxis *ax3 = Gbzx.GetXaxis();
        TAxis *ay3 = Gbzx.GetYaxis();
        ax3->SetTitle("z (m)");
        ay3->SetTitle("Bz (T)");
        TAxis *ax4 = Gbxx.GetXaxis();
        TAxis *ay4 = Gbxx.GetYaxis();
        ax4->SetTitle("x (m)");
        ay4->SetTitle("Bz (T)");
        TAxis *ax5 = Ghzz.GetXaxis();
        TAxis *ay5 = Ghzz.GetYaxis();
        ax5->SetTitle("z (m)");
        ay5->SetTitle("Bz (T)");
        TAxis *ax6 = Ghzx.GetXaxis();
        TAxis *ay6 = Ghzx.GetYaxis();
        ax6->SetTitle("z (m)");
        ay6->SetTitle("Bz (T)");
        TAxis *ax7 = GInvis2.GetXaxis();
        TAxis *ay7 = GInvis2.GetYaxis();
        ax7->SetTitle("x (m)");
        ay7->SetTitle("Bz (T)");
        GInvis2.SetPoint(0,0.,0.0038);
        GInvis2.SetPoint(1,0.,0.0042);
        GInvis2.SetPoint(2,0.044,0.0038);
        GInvis2.SetPoint(3,0.044,0.0042);
        TAxis *ax8 = Gar.GetXaxis();
        TAxis *ay8 = Gar.GetYaxis();
        ax8->SetTitle("z (m)");
        ay8->SetTitle("Bz (T)");
        TAxis *ax9 = Gfe.GetXaxis();
        TAxis *ay9 = Gfe.GetYaxis();
        ax9->SetTitle("z (m)");
        ay9->SetTitle("Bz (T)");
        TAxis *ax0 = Gxb.GetXaxis();
        TAxis *ay0 = Gxb.GetYaxis();
        ax0->SetTitle("z (m)");
        ay0->SetTitle("Bx (T)");
        TAxis *axA = Gxh.GetXaxis();
        TAxis *ayA = Gxh.GetYaxis();
        axA->SetTitle("z (m)");
        ayA->SetTitle("Bx (T)");
        TAxis *axB = Gtotb.GetXaxis();
        TAxis *ayB = Gtotb.GetYaxis();
        TAxis *azB = Gtotb.GetZaxis();
        axB->SetTitle("z (m)");
        ayB->SetTitle("x (m)");
        azB->SetTitle("Bz (T)");
        axB->SetTitleOffset(2.0);
        ayB->SetTitleOffset(2.0);
        azB->SetTitleOffset(2.0);
        TAxis *axC = GInvis.GetXaxis();
        TAxis *ayC = GInvis.GetYaxis();
        TAxis *azC = GInvis.GetZaxis();
        axC->SetTitle("z (m)");
        ayC->SetTitle("x (m)");
        azC->SetTitle("Bz (T)");
        axC->SetTitleOffset(2.0);
        ayC->SetTitleOffset(2.0);
        azC->SetTitleOffset(2.0);
        GInvis.SetPoint(0,0,0.04,0);
        GInvis.SetPoint(1,0,0.04,0.005);
        GInvis.SetPoint(2,0,-0.04,0);
        GInvis.SetPoint(3,0,-0.04,0.005);
        GInvis.SetPoint(4,0.12,0.04,0);
        GInvis.SetPoint(5,0.12,0.04,0.005);
        GInvis.SetPoint(6,0.12,-0.04,0);
        GInvis.SetPoint(7,0.12,-0.04,0.005);
    }

    for(int i=0;i<Calib.GetLines();++i){
        Gcalib.SetPoint(i,datac[i][0],datac[i][1]/1000);
    }

    double Rb=0.068; //m
    double Nb=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m
    double offset=0.000715773;

    auto lfit = [&](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];
    };
    TF1 *Ffit = new TF1("FIT", lfit, -10000,10000,2);
    
    Gcalib.Fit(Ffit);

    auto calib = [&](double *x,double *p=nullptr){
        return m0*Nb*(x[0]-offset)/(2*Rb*0.00610303);
    };
    TF1 *Fcalib = new TF1("FIT", calib, -10000,10000,0);

    offset=0.00070;
    for(int i=0;i<Bobinezz.GetLines();++i){
        Gbzz.SetPoint(i,databzz[i][0]/100,Fcalib->Eval(databzz[i][1]/1000));
        Gtotb.SetPoint(i,databzz[i][0]/100,0,Fcalib->Eval(databzz[i][1]/1000));
    }
    offset=0.00071;
    for(int i=0;i<Bobinezx.GetLines();++i){
        Gbzx.SetPoint(i,databzx[i][0]/100,Fcalib->Eval(databzx[i][1]/1000));
        Gtotb.SetPoint(i+Bobinezz.GetLines(),databzx[i][0]/100,0.025,Fcalib->Eval(databzx[i][1]/1000));
    }
    offset=0.0005;
    Gxb.SetPoint(0,4./100,Fcalib->Eval(-0.41/1000));
    Gxb.SetPoint(1,10./100,Fcalib->Eval(0.42/1000));
    offset=0.00078-0.00024;
    for(int i=0;i<Bobinexx.GetLines();++i){
        Gbxx.SetPoint(i,databxx[i][0]/100,Fcalib->Eval(databxx[i][1]/1000));
        Gtotb.SetPoint(i+Bobinezz.GetLines()+Bobinezx.GetLines(),0,databxx[i][0]/100,Fcalib->Eval(databxx[i][1]/1000));
    }
    offset=0.00080;
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        Ghzz.SetPoint(i,datahzz[i][0]/100,Fcalib->Eval(datahzz[i][1]/1000));
        Gtoth.SetPoint(i,datahzz[i][0]/100,0,Fcalib->Eval(datahzz[i][1]/1000));
    }
    offset=0.00074;
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        Ghzx.SetPoint(i,datahzx[i][0]/100,Fcalib->Eval(datahzx[i][1]/1000));
        Gtoth.SetPoint(i+Helmholtzzz.GetLines(),datahzz[i][0]/100,0.025,Fcalib->Eval(datahzz[i][1]/1000));
    }
    offset=0.0005;
    Gxh.SetPoint(0,0.,Fcalib->Eval(0.19/1000));
    Gxh.SetPoint(1,5.5/100,Fcalib->Eval(-0.92/1000));
    Gxh.SetPoint(2,10.5/100,Fcalib->Eval(0.04/1000));
    offset=0.00076-0.00018;
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        Ghxx.SetPoint(i,datahxx[i][0]/100,Fcalib->Eval(datahxx[i][1]/1000));
        Gtoth.SetPoint(i+Helmholtzzz.GetLines()+Helmholtzzx.GetLines(),0,datahxx[i][0]/100,Fcalib->Eval(datahxx[i][1]/1000));
    }
    offset=0.00054;
    for(int i=0;i<ar.GetLines();++i){
        Gar.SetPoint(i,dataa[i][0]/100,Fcalib->Eval(dataa[i][1]/1000));
    }
    offset=0.00054;
    double Lf=0.15;
    for(int i=0;i<ferro.GetLines();++i){
        Gfe.SetPoint(i,dataf[i][0]/100+Lf/2.,Fcalib->Eval(dataf[i][1]/1000));
    }
    
    double I=1;
    //Bobine circular
    //x=0 y=0
    auto ex = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]), 3./2.);
    };
    TF1 *fex= new TF1("F", ex, -0.15,0.15,1);
    auto Bx = [&](double *x,double *p=nullptr){
        fex->SetParameter(0, x[0]);
        double Bvalue=fex->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex= new TF1("F", Bx, -0.15,0.15,0);

    auto ez = [&](double *x,double *p=nullptr){
        return Rb/pow((Rb*Rb+p[0]*p[0]), 3./2.);
    };
    TF1 *fez= new TF1("F", ez, -0.15,0.15,1);
    
    auto Bz = [&](double *x,double *p=nullptr){
        fez->SetParameter(0, x[0]);
        double Bvalue=fez->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez= new TF1("F", Bz, -0.15,0.15,0);

    //x=0.025 y=0
    double xx=0.025; //m
    auto ex2 = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3./2.);
    };
    TF1 *fex2= new TF1("F", ex2, -0.15,0.15,1);
    
    auto Bx2 = [&](double *x,double *p=nullptr){
        fex2->SetParameter(0, x[0]);
        double Bvalue=fex2->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex2= new TF1("F", Bx2, -0.15,0.15,0);

    auto ez2 = [&](double *x,double *p=nullptr){
        return (Rb-xx*sin(x[0]))/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3./2.);
    };
    TF1 *fez2= new TF1("F", ez2, -0.15,0.15,1);


    auto Bz2 = [&](double *x,double *p=nullptr){
        fez2->SetParameter(0, x[0]);
        double Bvalue=fez2->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez2= new TF1("F", Bz2, -0.15,0.15,0);

    //y=0 z=0
    double L;
    auto exx =[&](double *x,double *p=nullptr){
        return ((L/2)*sin(x[0]))/pow(Rb*Rb+p[0]*p[0]+(L/2)*(L/2)-2*p[0]*Rb*sin(x[0]), 3./2.);
    };
    TF1 *fexx= new TF1("F", exx, -0.15,0.15,1);
    auto Bxx = [&](double *x,double *p=nullptr){
        fexx->SetParameter(0, x[0]);
        double Bvalue=fexx->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bexx= new TF1("F", Bxx, -0.15,0.15,0);

    auto ezx =[&](double *x,double *p=nullptr){
        return (Rb-p[0]*sin(x[0]))/pow(Rb*Rb+p[0]*p[0]+(L/2)*(L/2)-2*p[0]*Rb*sin(x[0]),3./2.);
    };
    TF1 *fezx= new TF1("F", ezx, -0.15,0.15,1);
    auto Bzx = [&](double *x,double *p=nullptr){
        fezx->SetParameter(0, x[0]);
        double Bvalue=fezx->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bezx= new TF1("F", Bzx, -0.15,0.15,0);

    //Bobines de Helmholtz
    //x=0 y=0
    auto Bh1x=[&](double *x,double *p=nullptr){
        return Bex->Eval(x[0]-L/2)+Bex->Eval(x[0]+L/2);
    };
    TF1 *Bh1ex= new TF1("F", Bh1x, -0.15,0.15,0);
    auto Bh1z=[&](double *x,double *p=nullptr){
        return Bez->Eval(x[0]-L/2)+Bez->Eval(x[0]+L/2);
    };
    TF1 *Bh1ez= new TF1("F", Bh1z, -0.15,0.15,0);

    //x=2.5 y=0
    auto Bh2x=[&](double *x,double *p=nullptr){
        return Bex2->Eval(x[0]-L/2)+Bex2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ex= new TF1("F", Bh2x, -0.15,0.15,0);
    auto Bh2z=[&](double *x,double *p=nullptr){
        return Bez2->Eval(x[0]-L/2)+Bez2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ez= new TF1("F", Bh2z, -0.15,0.15,0);
    
    //z=0 y=0
    auto Bh3x=[&](double *x,double *p=nullptr){
        return -Bexx->Eval(x[0])+Bexx->Eval(x[0]);
    };
    TF1 *Bh3ex= new TF1("F", Bh3x, -0.15,0.15,0);
    auto Bh3z=[&](double *x,double *p=nullptr){
        return 2*Bezx->Eval(x[0]);
    };
    TF1 *Bh3ez= new TF1("F", Bh3z, -0.15,0.15,0);

    //solenoides
    double Rar=0.02;
    double Lar=0.186;
    double Rf=0.028;
    double nar=39./0.03;
    double nf=45./0.03;

    auto Bzar = [&](double *x,double *p=nullptr){
        return m0*nar*I/2*((Lar/2-x[0])/sqrt((Lar/2-x[0])*(Lar/2-x[0])+Rar*Rar)+(Lar/2+x[0])/sqrt((Lar/2+x[0])*(Lar/2+x[0])+Rar*Rar));
    };
    TF1 *Bar= new TF1("F", Bzar, -0.15,0.15,0);

    auto Bzf = [&](double *x,double *p=nullptr){
        return m0*(nf*I+p[0])/2*((Lf/2-x[0])/sqrt((Lf/2-x[0])*(Lf/2-x[0])+Rf*Rf)+(Lf/2+x[0])/sqrt((Lf/2+x[0])*(Lf/2+x[0])+Rf*Rf));
    };
    TF1 *Bf= new TF1("F", Bzf, -0.15,0.15,1);

    //2D
    auto l3db = [&](double *x,double *p=nullptr){
        return (Rb-p[1]*sin(x[0]))/pow((Rb*Rb+p[0]*p[0]+p[1]*p[1]-2*Rb*p[1]*sin(x[0])), 3./2.);
    };
    TF1 *f3db= new TF1("F", l3db, -0.15,0.15,2);
    
    auto ltotb = [&](double *x,double *p=nullptr){
        f3db->SetParameter(0, x[0]);
        f3db->SetParameter(1, x[1]);
        double Bvalue=f3db->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF2 *ftotb= new TF2("F", ltotb, 0,0.12,-0.04,0.04,0);

    auto ltoth = [&](double *x,double *p=nullptr){
        return ftotb->Eval(x[0]-dbH/2,x[1])+ftotb->Eval(x[0]+dbH/2,x[1]);
    };
    TF2 *ftoth= new TF2("F", ltoth, 0,0.12,-0.04,0.04,0);

    TGraph corrb1;
    TGraph corrb2;
    TGraph corrb3;
    TGraph corrh1;
    TGraph corrh2;
    TGraph corrh3;
    TGraph corrar;
    TGraph corrfe;

    Bez->SetLineColor(kOrange-3);
    Bez2->SetLineColor(kOrange-3);
    Bezx->SetLineColor(kOrange-3);
    Bh1ez->SetLineColor(kViolet+2);
    Bh2ez->SetLineColor(kViolet+2);
    Bh3ez->SetLineColor(kViolet+2);

    //Draw
    TCanvas* c1 = new TCanvas("","",1200,800);
    c1->SetLeftMargin(0.2);
    Gcalib.Draw("AP");
    c1->SaveAs("calib.png");
    c1->Clear();
    //Bobine
    L=0;
    I=1.001;
    for (int i=0; i<Bobinezz.GetLines(); ++i){
        corrb1.SetPoint(i,Gbzz.GetY()[i],Bez->Eval(Gbzz.GetX()[i]));
    }
    Gbzz.Draw("AP");
    Bez->Draw("SAME");
    c1->SaveAs("bzz.png");
    c1->Clear();
    I=0.998;
    for (int i=0; i<Bobinezx.GetLines(); ++i){
        corrb2.SetPoint(i,Gbzx.GetY()[i],Bez2->Eval(Gbzx.GetX()[i]));
    }
    Gbzx.Draw("AP");
    Bez2->Draw("SAME");
    c1->SaveAs("bzx.png");
    c1->Clear();
    Gxb.Draw("AP");
    Bex2->Draw("SAME");
    c1->SaveAs("bex.png");
    c1->Clear();
    I=0.997;
    for (int i=0; i<Bobinexx.GetLines(); ++i){
        corrb3.SetPoint(i,Gbxx.GetY()[i],Bezx->Eval(Gbxx.GetX()[i]));
    }
    Gbxx.Draw("AP");
    Bezx->Draw("SAME");
    c1->SaveAs("bxx.png");
    c1->Clear();
    //Helmholtz
    I=0.995;
    for (int i=0; i<Helmholtzzz.GetLines(); ++i){
        corrh1.SetPoint(i,Ghzz.GetY()[i],Bh1ez->Eval(Ghzz.GetX()[i]));
    }
    L=dbH;
    Ghzz.Draw("AP");
    Bh1ez->Draw("SAME");
    c1->SaveAs("hzz.png");
    c1->Clear();
    I=0.993;
    for (int i=0; i<Helmholtzzx.GetLines(); ++i){
        corrh2.SetPoint(i,Ghzx.GetY()[i],Bh2ez->Eval(Ghzx.GetX()[i]));
    }
    Ghzx.Draw("AP");
    Bh2ez->Draw("SAME");
    c1->SaveAs("hzx.png");
    c1->Clear();
    Gxh.Draw("AP");
    Bh2ex->Draw("SAME");
    c1->SaveAs("hex.png");
    c1->Clear();
    I=0.993;
    for (int i=0; i<Helmholtzxx.GetLines(); ++i){
        corrh3.SetPoint(i,Ghxx.GetY()[i],Bh3ez->Eval(Ghxx.GetX()[i]));
    }
    GInvis2.Draw("AP");
    Ghxx.Draw("P SAME");
    Bh3ez->Draw("SAME");
    c1->SaveAs("hxx.png");
    c1->Clear();
    //Solenoides
    I=0.995;
    for (int i=0; i<ar.GetLines(); ++i){
        corrar.SetPoint(i,Gar.GetY()[i],Bar->Eval(Gar.GetX()[i]));
    }
    Gar.Draw("AP");
    Bar->Draw("SAME");
    c1->SaveAs("ar.png");
    c1->Clear();
    I=0.993;
    for (int i=0; i<ferro.GetLines(); ++i){
        corrfe.SetPoint(i,Gfe.GetY()[i],Bf->Eval(Gfe.GetX()[i]));
    }
    Gfe.Fit(Bf);
    Gfe.Draw("AP");
    c1->SaveAs("fe.png");
    c1->Clear();
    //3D
    TGraph2D G3Db; G3Db.SetTitle(""); G3Db.SetLineColor(kGreen); G3Db.SetMarkerStyle(8); G3Db.SetMarkerColor(kGreen); G3Db.SetMarkerSize(.5);
    TGraph2D G3Dh; G3Dh.SetTitle(""); G3Dh.SetLineColor(kGreen); G3Dh.SetMarkerStyle(8); G3Dh.SetMarkerColor(kGreen); G3Dh.SetMarkerSize(.5);
    int numpnts = 25;
    for(int j = 0; j<numpnts; ++j){
        for(int l=0; l<numpnts; ++l){
            G3Db.SetPoint(l+numpnts*j,0.12/numpnts*j,-0.04+0.08/numpnts*l,ftotb->Eval(0.12/numpnts*j,-0.04+0.08/numpnts*l));
            G3Dh.SetPoint(l+numpnts*j,0.12/numpnts*j,-0.04+0.08/numpnts*l,ftoth->Eval(0.12/numpnts*j,-0.04+0.08/numpnts*l));
        }
    }
    I=1;
    Gtotb.Draw("P");
    G3Db.Draw("P TRIW SAME");
    c1->SetPhi(330.);
    c1->SaveAs("3Db.png");
    c1->Clear();
    GInvis.Draw("P");
    Gtoth.Draw("P SAME");
    G3Dh.Draw("P TRIW SAME");
    c1->SetPhi(330.);
    c1->SaveAs("3Dh.png");
    c1->Clear();

    double Exb1=corrb1.GetMean(1);
    double Eyb1=corrb1.GetMean(2);
    double Exb2=corrb2.GetMean(1);
    double Eyb2=corrb2.GetMean(2);
    double Exb3=corrb3.GetMean(1);
    double Eyb3=corrb3.GetMean(2);
    double Exh1=corrh1.GetMean(1);
    double Eyh1=corrh1.GetMean(2);
    double Exh2=corrh2.GetMean(1);
    double Eyh2=corrh2.GetMean(2);
    double Exh3=corrh3.GetMean(1);
    double Eyh3=corrh3.GetMean(2);
    double Exar=corrar.GetMean(1);
    double Eyar=corrar.GetMean(2);
    double Exfe=corrfe.GetMean(1);
    double Eyfe=corrfe.GetMean(2);

    double covb1=0;
    double vxb1=0;
    double vyb1=0;
    double covb2=0;
    double vxb2=0;
    double vyb2=0;
    double covb3=0;
    double vxb3=0;
    double vyb3=0;
    double covh1=0;
    double vxh1=0;
    double vyh1=0;
    double covh2=0;
    double vxh2=0;
    double vyh2=0;
    double covh3=0;
    double vxh3=0;
    double vyh3=0;
    double covar=0;
    double vxar=0;
    double vyar=0;
    double covfe=0;
    double vxfe=0;
    double vyfe=0;

    for (int i = 0; i<corrb1.GetN(); ++i){
        covb1+=(corrb1.GetX()[i]-Exb1)*(corrb1.GetY()[i]-Eyb1);
        vxb1+=(corrb1.GetX()[i]-Exb1)*(corrb1.GetX()[i]-Exb1);
        vyb1+=(corrb1.GetY()[i]-Eyb1)*(corrb1.GetY()[i]-Eyb1);
    }
    covb1/=corrb1.GetN();
    vxb1/=corrb1.GetN();
    vyb1/=corrb1.GetN();
    double Rb1=covb1/sqrt(vxb1*vyb1);

    for (int i = 0; i<corrb2.GetN(); ++i){
        covb2+=(corrb2.GetX()[i]-Exb2)*(corrb2.GetY()[i]-Eyb2);
        vxb2+=(corrb2.GetX()[i]-Exb2)*(corrb2.GetX()[i]-Exb2);
        vyb2+=(corrb2.GetY()[i]-Eyb2)*(corrb2.GetY()[i]-Eyb2);
    }
    covb2/=corrb2.GetN();
    vxb2/=corrb2.GetN();
    vyb2/=corrb2.GetN();
    double Rb2=covb2/sqrt(vxb2*vyb2);

    for (int i = 0; i<corrb3.GetN(); ++i){
        covb3+=(corrb3.GetX()[i]-Exb3)*(corrb3.GetY()[i]-Eyb3);
        vxb3+=(corrb3.GetX()[i]-Exb3)*(corrb3.GetX()[i]-Exb3);
        vyb3+=(corrb3.GetY()[i]-Eyb3)*(corrb3.GetY()[i]-Eyb3);
    }
    covb3/=corrb3.GetN();
    vxb3/=corrb3.GetN();
    vyb3/=corrb3.GetN();
    double Rb3=covb3/sqrt(vxb3*vyb3);

    for (int i = 0; i<corrh1.GetN(); ++i){
        covh1+=(corrh1.GetX()[i]-Exh1)*(corrh1.GetY()[i]-Eyh1);
        vxh1+=(corrh1.GetX()[i]-Exh1)*(corrh1.GetX()[i]-Exh1);
        vyh1+=(corrh1.GetY()[i]-Eyh1)*(corrh1.GetY()[i]-Eyh1);
    }
    covh1/=corrh1.GetN();
    vxh1/=corrh1.GetN();
    vyh1/=corrh1.GetN();
    double Rh1=covh1/sqrt(vxh1*vyh1);

    for (int i = 0; i<corrh2.GetN(); ++i){
        covh2+=(corrh2.GetX()[i]-Exh2)*(corrh2.GetY()[i]-Eyh2);
        vxh2+=(corrh2.GetX()[i]-Exh2)*(corrh2.GetX()[i]-Exh2);
        vyh2+=(corrh2.GetY()[i]-Eyh2)*(corrh2.GetY()[i]-Eyh2);
    }
    covh2/=corrh2.GetN();
    vxh2/=corrh2.GetN();
    vyh2/=corrh2.GetN();
    double Rh2=covh2/sqrt(vxh2*vyh2);

    for (int i = 0; i<corrh3.GetN(); ++i){
        covh3+=(corrh3.GetX()[i]-Exh3)*(corrh3.GetY()[i]-Eyh3);
        vxh3+=(corrh3.GetX()[i]-Exh3)*(corrh3.GetX()[i]-Exh3);
        vyh3+=(corrh3.GetY()[i]-Eyh3)*(corrh3.GetY()[i]-Eyh3);
    }
    covh3/=corrh3.GetN();
    vxh3/=corrh3.GetN();
    vyh3/=corrh3.GetN();
    double Rh3=covh3/sqrt(vxh3*vyh3);

    for (int i = 0; i<corrar.GetN(); ++i){
        covar+=(corrar.GetX()[i]-Exar)*(corrar.GetY()[i]-Eyar);
        vxar+=(corrar.GetX()[i]-Exar)*(corrar.GetX()[i]-Exar);
        vyar+=(corrar.GetY()[i]-Eyar)*(corrar.GetY()[i]-Eyar);
    }
    covar/=corrar.GetN();
    vxar/=corrar.GetN();
    vyar/=corrar.GetN();
    double Rhoar=covar/sqrt(vxar*vyar);

    for (int i = 0; i<corrfe.GetN(); ++i){
        covfe+=(corrfe.GetX()[i]-Exfe)*(corrfe.GetY()[i]-Eyfe);
        vxfe+=(corrfe.GetX()[i]-Exfe)*(corrfe.GetX()[i]-Exfe);
        vyfe+=(corrfe.GetY()[i]-Eyfe)*(corrfe.GetY()[i]-Eyfe);
    }
    covfe/=corrfe.GetN();
    vxfe/=corrfe.GetN();
    vyfe/=corrfe.GetN();
    double Rfe=covfe/sqrt(vxfe*vyfe);

    cout<<"b1:  "<<Rb1<<endl;
    cout<<"b2:  "<<Rb2<<endl;
    cout<<"b3:  "<<Rb3<<endl;
    cout<<"h1:  "<<Rh1<<endl;
    cout<<"h2:  "<<Rh2<<endl;
    cout<<"h3:  "<<Rh3<<endl;
    cout<<"ar:  "<<Rhoar<<endl;
    cout<<"fe:  "<<Rfe<<endl;

    return 0;
}