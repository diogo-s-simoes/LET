#include "Integrator.h"
#include "Func1D.h"
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

int main(){

    double Rb=0.068; //m
    double Nb=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m

    auto calib = [&](double *x,double *p=nullptr){
        return m0*Nb*x[0]/(2*Rb);
    };
    TF1 *Fit1 = new TF1("FIT", calib, -0.15,0.15,0);

    
    double I=1;
    double err=0;
    auto ex = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]), 3./2.);
    };
    TF1 *fex= new TF1("F", ex, -0.15,0.15,1);
    //Bobine circular
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
    double L=0;
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
    auto Bh1x=[&](double *x,double *p=nullptr){
        return Bex->Eval(x[0]-L/2)+Bex->Eval(x[0]+L/2);
    };
    TF1 *Bh1ex= new TF1("F", Bh1x, -0.15,0.15,0);
    auto Bh1z=[&](double *x,double *p=nullptr){
        return Bez->Eval(x[0]-L/2)+Bez->Eval(x[0]+L/2);
    };
    TF1 *Bh1ez= new TF1("F", Bh1z, -0.15,0.15,0);

    auto Bh2x=[&](double *x,double *p=nullptr){
        return Bex2->Eval(x[0]-L/2)+Bex2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ex= new TF1("F", Bh2x, -0.15,0.15,0);
    auto Bh2z=[&](double *x,double *p=nullptr){
        return Bez2->Eval(x[0]-L/2)+Bez2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ez= new TF1("F", Bh2z, -0.15,0.15,0);

    L=dbH;
    auto Bh3x=[&](double *x,double *p=nullptr){
        return -Bexx->Eval(x[0])+Bexx->Eval(x[0]);
    };
    TF1 *Bh3ex= new TF1("F", Bh3x, -0.15,0.15,0);
    auto Bh3z=[&](double *x,double *p=nullptr){
        return Bezx->Eval(x[0])+Bezx->Eval(x[0]);
    };
    TF1 *Bh3ez= new TF1("F", Bh3z, -0.15,0.15,0);

    //solenoides
    double Rar=0.02;
    double Lar=0.186;
    double Rf=0.028;
    double Lf=0.15;
    double nar=39./0.03;
    double nf=45./0.03;

    auto Bzar = [&](double *x,double *p=nullptr){
        return m0*nar*I/2*((Lar/2-x[0])/sqrt((Lar/2-x[0])*(Lar/2-x[0])+Rar*Rar)+(Lar/2+x[0])/sqrt((Lar/2+x[0])*(Lar/2+x[0])+Rar*Rar));
    };
    TF1 *Bar= new TF1("F", Bzar, -0.15,0.15,0);

    auto Bzf = [&](double *x,double *p=nullptr){
        return m0*(nf*I+p[0])/2*((Lf/2-x[0])/sqrt((Lf/2-x[0])*(Lf/2-x[0])+Rf*Rf)+(Lf/2+x[0])/sqrt((Lf/2+x[0])*(Lf/2+x[0])+Rf*Rf));
    };
    TF1 *Bf= new TF1("F", Bzf, -0.15,0.15,2);

    return 0;
}

