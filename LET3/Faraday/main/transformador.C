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
#include "TRandom3.h"

int main(){
    DataReader transformador1("data/transformador1.txt");
    DataReader transformador2("data/transformador2.txt");
    DataReader transformador3("data/transformador3.txt");
    DataReader transformador4("data/transformador4.txt");
    DataReader transformador5("data/transformador5.txt");

    vector<vector<double>> tf50;
    vector<vector<double>> tf100;
    vector<vector<double>> tf500;
    vector<vector<double>> tf1000;
    vector<vector<double>> tf2500;

    vector<double> temp;

    for(int i=0;i<transformador1.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(stod(transformador1.GetData()[i][j]));
        }
        tf50.push_back(temp);
        temp.clear();
    }

    for(int i=0;i<transformador2.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(stod(transformador2.GetData()[i][j]));
        }
        tf100.push_back(temp);
        temp.clear();
    }

    for(int i=0;i<transformador3.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(stod(transformador3.GetData()[i][j]));
        }
        tf500.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<transformador4.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(stod(transformador4.GetData()[i][j]));
        }
        tf1000.push_back(temp);
        temp.clear();
    }

    for(int i=0;i<transformador5.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(stod(transformador5.GetData()[i][j]));
           // cout << stod(transformador5.GetData()[i][j]) <<endl;
        }
        tf2500.push_back(temp);
        temp.clear();
    }

/*
    auto id = [&](double *x,double *p=nullptr){
        return 0.12*x[0];
    };
    TF1 *IDEAL= new TF1("F", id, -0.15,0.15,1);
*/


    TGraph IDEAL; IDEAL.SetTitle(""); IDEAL.SetLineColor(kBlack); IDEAL.SetLineWidth(3);
    TGraph TF50; TF50.SetTitle(""); TF50.SetLineColor(kAzure-4); TF50.SetLineWidth(3); TF50.SetMarkerStyle(8); TF50.SetMarkerColor(kAzure); TF50.SetMarkerSize(1);
    TGraph TF100; TF100.SetTitle(""); TF100.SetLineColor(kGreen); TF100.SetLineWidth(3); TF100.SetMarkerStyle(33); TF100.SetMarkerColor(kGreen+2); TF100.SetMarkerSize(2);
    TGraph TF500; TF50.SetTitle(""); TF500.SetLineColor(kOrange+7); TF500.SetLineWidth(3); TF500.SetMarkerStyle(22); TF500.SetMarkerColor(kOrange+2); TF500.SetMarkerSize(1.6);
    TGraph TF1000; TF1000.SetTitle(""); TF1000.SetLineColor(kViolet); TF1000.SetLineWidth(3); TF1000.SetMarkerStyle(23); TF1000.SetMarkerColor(kViolet+2); TF1000.SetMarkerSize(1.6);
    TGraph TF2500; TF2500.SetTitle(""); TF2500.SetLineColor(kMagenta); TF2500.SetLineWidth(3); TF2500.SetMarkerStyle(34); TF2500.SetMarkerColor(kMagenta+2); TF2500.SetMarkerSize(1.6);

   
    TGraph2D G2D; G2D.SetTitle(""); G2D.SetLineColor(kRed); G2D.SetMarkerStyle(8); G2D.SetMarkerColor(kRed); G2D.SetMarkerSize(2); G2D.GetXaxis()->SetTitle("oi");
   
    IDEAL.SetPoint(0,0,0);
    IDEAL.SetPoint(1,9,1.08);
   
    int ofset=0;

    for(int i=0;i<transformador1.GetLines();++i){
        TF50.SetPoint(i,tf50[i][0],tf50[i][1]/1000);
        G2D.SetPoint(i,tf50[i][0],tf50[i][1]/1000,50.);
    }
    ofset+=transformador1.GetLines();
    
    for(int i=0;i<transformador2.GetLines();++i){
        TF100.SetPoint(i,tf100[i][0],tf100[i][1]/1000);
        G2D.SetPoint(i+ofset,tf100[i][0],tf100[i][1]/1000,100.);
    }
    ofset+=transformador2.GetLines();

    for(int i=0;i<transformador3.GetLines();++i){
        TF500.SetPoint(i,tf500[i][0],tf500[i][1]/1000);
        G2D.SetPoint(i+ofset,tf500[i][0],tf500[i][1]/1000,500);
    }
    ofset+=transformador3.GetLines();
    
    for(int i=0;i<transformador4.GetLines();++i){
        TF1000.SetPoint(i,tf1000[i][0],tf1000[i][1]/1000);
        G2D.SetPoint(i+ofset,tf1000[i][0],tf1000[i][1]/1000,1000.);
    }
    ofset+=transformador4.GetLines();
    
    for(int i=0;i<transformador5.GetLines();++i){
        TF2500.SetPoint(i,tf2500[i][0],tf2500[i][1]/1000);
        G2D.SetPoint(i+ofset,tf2500[i][0],tf2500[i][1]/1000,2500.);
    }




    auto lfit = [&](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];    //V2 = (n2/n1) * V1 +0
    };
    TF1 *Ffit = new TF1("FIT", lfit, -10000,10000,2);
    


 //COMO APAGAR LINHAS VERMELHAS DO FIT?????
    //TF50.Fit(Ffit);
    //TF100.Fit(Ffit);
    //TF500.Fit(Ffit);
    //TF1000.Fit(Ffit);
    //TF2500.Fit(Ffit); //ESTE NAO ESTA A FUNCIONARR NAO APERECE NO GRAFICO 

    TCanvas* c1 = new TCanvas("","",1200,800);
    TMultiGraph* mult1= new TMultiGraph(); mult1->SetTitle("Transformador");



  gPad->SetGrid(1, 1); gPad->Update();

	mult1->Add(&IDEAL);
	mult1->Add(&TF50);
	mult1->Add(&TF100);
	mult1->Add(&TF500);
	//mult1->Add(&TF1000);
    mult1->Draw("APL");

    auto legend1 = new TLegend(0.1,0.7,0.4,.9);
    legend1->SetTextFont(62);
    legend1->SetTextSize(0.03);
    legend1->AddEntry(&IDEAL,"Transformador ideal","l");
    legend1->AddEntry(&TF50,"f=50Hz","l");
    legend1->AddEntry(&TF100,"f=100Hz","l");
    legend1->AddEntry(&TF500,"f=500hZ","l");
    //legend1->AddEntry(&TF1000,"f=1000Hz","l");
    legend1->AddEntry(&TF2500,"f=2500Hz","l");
    legend1->Draw("same");
    c1->SaveAs("transformadorideal.png");
    c1->Clear();



/*
    TF50.Draw("AP");
    TF100.Draw("same");
    TF500.Draw("same");
    TF1000.Draw("same");
    c1->SaveAs("transformadorideal.png");
    c1->Clear();*/


    auto l2Dfit = [&](double *x,double *p=nullptr){
        double mu=4000;
        double l=.48;
        double A=16*1e-6;
        double n1=600;
        double n2=72;
        double R=10;
        double V=.48*16*1e-6;
        double a=p[1];
        double ex=p[2];

        return (x[0]*x[0]/p[0]/n1-x[1]*x[1]/(p[0]*n2+R))/pow(V*a*pow(1/p[0]*x[0]-n2/(n2*p[0]+R)*x[1],ex),p[3])*l/A/mu;
    };

    TF2 *f2Dfit= new TF2("F", l2Dfit, 0.01,10,0.01,2,4);

    f2Dfit->SetParameter(0,0.000671576);
    f2Dfit->SetParameter(1,2.11586);
    f2Dfit->SetParameter(2,1.17312);
    f2Dfit->SetParameter(3,1.69224);

    TRandom3 Rand(0);
    double chi2=1e100;
    double pr0;
    double pr1;
    double pr2;
    double pr3;
    for(int i = 0; i<1e6; ++i){
        double chit=0;
        f2Dfit->SetParameter(0,Rand.Rndm()*0.1);
        f2Dfit->SetParameter(1,Rand.Rndm()*5e-2);
        f2Dfit->SetParameter(2,Rand.Rndm()*5);
        f2Dfit->SetParameter(3,Rand.Rndm()*5);
        for(int k = 0; k<G2D.GetN(); ++k){
            chit+=pow(G2D.GetZ()[k]-f2Dfit->Eval(G2D.GetX()[k],G2D.GetY()[k]),2);
        }
        if(chit<chi2){
            chi2=chit;
            pr0=f2Dfit->GetParameter(0);
            pr1=f2Dfit->GetParameter(1);
            pr2=f2Dfit->GetParameter(2);
            pr3=f2Dfit->GetParameter(3);
        }
    }

    cout<<"CHI2="<<chi2<<endl<<"p[0]="<<pr0<<endl<<"p[1]="<<pr1<<endl<<"p[2]="<<pr2<<endl<<"p[3]="<<pr3<<endl;

    f2Dfit->SetParameter(0,pr0);
    f2Dfit->SetParameter(1,pr1);
    f2Dfit->SetParameter(2,pr2);
    f2Dfit->SetParameter(3,pr3);
    
    /*G2D.Fit(f2Dfit);
    double chifit=0;
    for(int k = 0; k<G2D.GetN(); ++k){
            chifit+=pow(G2D.GetZ()[k]-f2Dfit->Eval(G2D.GetX()[k],G2D.GetY()[k]),2);
    }
    cout<<"fit: "<<chifit<<endl;*/

    TGraph2D Gfunc; Gfunc.SetTitle(""); Gfunc.SetLineColor(kGreen); Gfunc.SetMarkerStyle(8); Gfunc.SetMarkerColor(kGreen); Gfunc.SetMarkerSize(1);
    int numpnts = 25;
    for(int j = 0; j<numpnts; ++j){
        for(int l=0; l<numpnts; ++l){
            Gfunc.SetPoint(l+numpnts*j,1+10./numpnts*j,0.01+1./numpnts*l,f2Dfit->Eval(1+10./numpnts*j,0.01+1./numpnts*l));
        }
    }
    
    G2D.Draw("P");
    Gfunc.Draw("TRIW SAME");
    c1->SetPhi(330.);
    c1->SaveAs("2Dgraph.png");
    c1->Clear();


    return 0;
}