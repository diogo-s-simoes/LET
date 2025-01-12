#include <cmath>
#include "DataReader.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "ODEsolver.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"



double coth(double x){
  return (exp(2*x)+1)/(exp(2*x)-1);
}


int main(){

  //read file
  DataReader ficheiro1("data/histerese2.txt");

  vector<vector<double>> DADOS;

  vector<double> temp1;

  int N=ficheiro1.GetLines();
  cout<<N<<endl;

  for(int i=0;i<N;++i){
    for(int j = 0;j<17;++j){
      temp1.push_back(stod(ficheiro1.GetData()[i][j]));
      cout<<stod(ficheiro1.GetData()[i][j])<<"   "<<flush;
    }
    cout<<endl;
    DADOS.push_back(temp1);
    temp1.clear();
    cout<<endl;
    
  }




  DataReader ficheiro2("data/histerese1.txt");

  vector<vector<double>> DADOS2;

  vector<double> temp2;

  N=ficheiro2.GetLines();
  cout<<N<<endl;

  for(int i=0;i<N;++i){
    for(int j = 0;j<17;++j){
      temp2.push_back(stod(ficheiro2.GetData()[i][j]));
      cout<<stod(ficheiro2.GetData()[i][j])<<"   "<<flush;
    }
    cout<<endl;
    DADOS2.push_back(temp2);
    temp2.clear();
    cout<<endl;
    
  }



  TGraphErrors *Hysteresisis = new TGraphErrors[DADOS.size()];
  TGraph HCoerc,Bsat,Brem,Bsmol;
  HCoerc.SetMarkerStyle(33);
  Bsat.SetMarkerStyle(33);
  Bsmol.SetMarkerStyle(33);
  Brem.SetMarkerStyle(33);
  HCoerc.SetMarkerColor(kGreen+2);
  Bsat.SetMarkerColor(kAzure-3);
  Bsmol.SetMarkerColor(kAzure-3);
  Brem.SetMarkerColor(kViolet+2);
  HCoerc.SetMarkerSize(2.5);
  Bsat.SetMarkerSize(2.5);
  Bsmol.SetMarkerSize(2.5);
  Brem.SetMarkerSize(2.5);
  TAxis *ax1 = HCoerc.GetXaxis();
  TAxis *ay1 = HCoerc.GetYaxis();
  ay1->SetTitle("H_{c} (A/m)");
  ax1->SetTitle("H_{max} (A/m)");
  TAxis *ax2 = Bsat.GetXaxis();
  TAxis *ay2 = Bsat.GetYaxis();
  ay2->SetTitle("B_{max} (T)");
  ax2->SetTitle("H_{max} (A/m)");
  TAxis *axs = Bsmol.GetXaxis();
  TAxis *ays = Bsmol.GetYaxis();
  ays->SetTitle("B_{max} (T)");
  axs->SetTitle("H_{max} (A/m)");
  TAxis *ax3 = Brem.GetXaxis();
  TAxis *ay3 = Brem.GetYaxis();
  ay3->SetTitle("B_{rem} (T)");
  ax3->SetTitle("H_{max} (A/m)");


    double ConvB=10*0.1/(49.*15.4e-4);
    double ConvH=10*505/0.48;

  for(int i=0;i<DADOS.size();i++){
    double Hm,HM,Bm,BM,B0m,B0M,H0m,H0M;

    double eHm,eHM,eBm,eBM,eB0m,eB0M,eH0m,eH0M;

    double scale=0.;

    if(DADOS[i][16]==1)
      scale = .4;
    else if(DADOS[i][16]==2)
      scale = 1.;
    else if(DADOS[i][16]==3)
      scale = 4.;


    Hm=0.001*(DADOS[i][0]+DADOS[i][1])/2*scale*ConvH;
    HM=0.001*(DADOS[i][2]+DADOS[i][3])/2*scale*ConvH;
    Bm=0.001*(DADOS[i][4]+DADOS[i][5])/2*ConvB;
    BM=0.001*(DADOS[i][6]+DADOS[i][7])/2*ConvB;
    B0m=0.001*(DADOS[i][8]+DADOS[i][9])/2*ConvB;
    B0M=0.001*(DADOS[i][10]+DADOS[i][11])/2*ConvB;
    H0m=0.001*(DADOS[i][12]+DADOS[i][13])/2*scale*ConvH;
    H0M=0.001*(DADOS[i][14]+DADOS[i][15])/2*scale*ConvH;



    eHm=0.001*(DADOS[i][0]-DADOS[i][1])/2*scale*ConvH;
    eHM=0.001*(DADOS[i][2]-DADOS[i][3])/2*scale*ConvH;
    eBm=0.001*(DADOS[i][4]-DADOS[i][5])/2*ConvB;
    eBM=0.001*(DADOS[i][6]-DADOS[i][7])/2*ConvB;
    eB0m=0.001*(DADOS[i][8]-DADOS[i][9])/2*ConvB;
    eB0M=0.001*(DADOS[i][10]-DADOS[i][11])/2*ConvB;
    eH0m=0.001*(DADOS[i][12]-DADOS[i][13])/2*scale*ConvH;
    eH0M=0.001*(DADOS[i][14]-DADOS[i][15])/2*scale*ConvH;



    Hysteresisis[i].SetPoint(0,Hm,Bm);
    Hysteresisis[i].SetPointError(0,eHm,eBm);
    Hysteresisis[i].SetPoint(1,HM,BM);
    Hysteresisis[i].SetPointError(1,eHM,eBM);
    Hysteresisis[i].SetPoint(2,H0m,0.);
    Hysteresisis[i].SetPointError(2,eH0m,0.);
    Hysteresisis[i].SetPoint(3,H0m,0.);
    Hysteresisis[i].SetPointError(3,eH0m,0.);
    Hysteresisis[i].SetPoint(4,0,B0m);
    Hysteresisis[i].SetPointError(4,0.,eB0m);
    Hysteresisis[i].SetPoint(5,0,B0m);
    Hysteresisis[i].SetPointError(5,0.,eB0m);


    Bsat.SetPoint(i,(HM-Hm)/2,(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2);
    if(i==4||i==3||i==5) Bsmol.SetPoint(i,(HM-Hm)/2,(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2);
    //cout<<"1 "<<i<<" "<<(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2<<endl;
    //cout<<HM<<"   "<<1.25663*1e-6*(HM-Hm)/2<<endl;
    Brem.SetPoint(i,(HM-Hm)/2,(B0M-B0m)/2-1.25663*1e-6*(HM-Hm)/2);
    HCoerc.SetPoint(i,(HM-Hm)/2,(H0M-H0m)/2);
  }



  for(int i=0;i<DADOS2.size();i++){
    double Hm,HM,Bm,BM,B0m,B0M,H0m,H0M;

    double eHm,eHM,eBm,eBM,eB0m,eB0M,eH0m,eH0M;

    double scale=0.;

    if(DADOS2[i][16]==1)
      scale = .4;
    else if(DADOS2[i][16]==2)
      scale = 1.;
    else if(DADOS2[i][16]==3)
      scale = 4.;


    Hm=0.001*(DADOS2[i][0]+DADOS2[i][1])/2*scale*ConvH;
    HM=0.001*(DADOS2[i][2]+DADOS2[i][3])/2*scale*ConvH;
    Bm=0.001*(DADOS2[i][4]+DADOS2[i][5])/2*ConvB;
    BM=0.001*(DADOS2[i][6]+DADOS2[i][7])/2*ConvB;
    B0m=0.001*(DADOS2[i][8]+DADOS2[i][9])/2*ConvB;
    B0M=0.001*(DADOS2[i][10]+DADOS2[i][11])/2*ConvB;
    H0m=0.001*(DADOS2[i][12]+DADOS2[i][13])/2*scale*ConvH;
    H0M=0.001*(DADOS2[i][14]+DADOS2[i][15])/2*scale*ConvH;


    Bsat.SetPoint(i+DADOS.size(),(HM-Hm)/2,(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2);
    //cout<<HM<<"   "<<1.25663*1e-6*(HM-Hm)/2<<endl;
    if(i==0||i==1) Bsmol.SetPoint(i+2,(HM-Hm)/2,(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2);
    //cout<<"2 "<<i<<" "<<(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2<<endl;
    Brem.SetPoint(i+DADOS.size(),(HM-Hm)/2,(B0M-B0m)/2-1.25663*1e-6*(HM-Hm)/2);
    HCoerc.SetPoint(i+DADOS.size(),(HM-Hm)/2,(H0M-H0m)/2);
  }

  auto llinfit = [&](double *x,double *p=nullptr){
    return p[0]*x[0];
  };
  TF1 *Flinfit= new TF1("F", llinfit, -1000,1000,1);

  Bsmol.Fit(Flinfit);  

  TCanvas* c1 = new TCanvas("","",1200,800);
    c1->SetLeftMargin(0.2);
    Bsat.Draw("AP");
    c1->SaveAs("Saturado.png");
    c1->Clear();
    Bsmol.Draw("AP");
    c1->SaveAs("Smol.png");
    c1->Clear();
    HCoerc.Draw("AP");
    c1->SaveAs("Coerc.png");
    c1->Clear();
    Brem.Draw("AP");
    c1->SaveAs("Reman.png");
    c1->Clear();



 //p[0]=M(0)   //p[1]=c  //p[2]=a  //p[3]=alpha  //p[4]=k
  auto li2 = [&](double *x,double *p=nullptr){
    double Ms= (4.67726e-17)*(2.33088e22);
    double delta =1;
    return (p[1]*Ms/p[2]*(1-coth((x[1]+p[3]*x[0])/p[2])*coth((x[1]+p[3]*x[0])/p[2])+(p[2]/(x[1]+p[3]*x[0]))*(p[2]/(x[1]+p[3]*x[0])))+(1-p[1])*(Ms*(coth((x[1]+p[3]*x[0])/p[2])-p[2]/(x[1]+p[3]*x[0]))-x[0])/(p[4]*delta*(1-p[1])-p[3]*((Ms*(coth((x[1]+p[3]*x[0])/p[2])-p[2]/(x[1]+p[3]*x[0])))-x[0])))/(1-p[3]*p[1]);
  };
  TF1 *Fn= new TF1("F", li2, -10000,10000,5);



  auto lt = [&](double *x,double *p=nullptr){
    vector<double> v;
    v.push_back(0.);
    ODEpoint P0(0,v);



    Fn->SetParameter(0,1);
    Fn->SetParameter(1,p[1]);
    Fn->SetParameter(2,p[2]);
    Fn->SetParameter(3,p[3]);
    Fn->SetParameter(4,p[4]);

    vector<TF1> VF;
    VF.push_back(*Fn);
    ODEsolver S(VF);
    double h = 10;
    double tmax = 9000;
    vector<ODEpoint> P = S.RK4(P0, h, x[0]);

    //cout << "oi:"<< P[0][2] <<endl;

    return P.back()[0];
  };

  TF1 *Ft= new TF1("F", lt, 0,200,5);

  //  Bsat.Fit(Ft);
    //Hysteresisis->SetMarkerSize(1.5); 
    //Hysteresisis->SetMarkerStyle(33);
    //Hysteresisis->SetMarkerColor(kRed);
    //Hysteresisis->Draw("AP");
    Ft->SetParameter(0,0);
    Ft->SetParameter(1,6.885e-3);
    Ft->SetParameter(2,70);
    Ft->SetParameter(3,1e-4);
    Ft->SetParameter(4,200);
    //Bsat.Fit(Ft);


    //Bsat.Draw("APL");
    //Ft->Draw("same");

    //c1->SaveAs("Hysteresisis.png");
    //c1->Clear();



    cout<<"Coerc:"<<TMath::MaxElement(HCoerc.GetN(),HCoerc.GetY())<<endl;
    cout<<"Sat:"<<TMath::MaxElement(Bsat.GetN(),Bsat.GetY())<<endl;
    cout<<"Rem:"<<TMath::MaxElement(Brem.GetN(),Brem.GetY())<<endl;
    double mu0=1.2566370614e-6;
    cout<<"mu_r: "<<Flinfit->GetParameter(0)/mu0<<endl;

  return 0;
}