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

double angconv(double g, double m, double s){
    return (M_PI/180.)*(g+m/60.+s/(30.*120.));
}

int main(){
    DataReader ficheiro1("data/Tabela1_PolS_FacePlana.txt");
    DataReader ficheiro2("data/Tabela2_PolS_FaceCurva.txt");
    DataReader ficheiro3("data/Tabela3_PolP_FacePlana.txt");
    DataReader ficheiro4("data/Tabela4_PolP_FaceCurva.txt");

    vector<vector<double>> data1;
    vector<vector<double>> data2;
    vector<vector<double>> data3;
    vector<vector<double>> data4;

    vector<double> temp1;
    vector<double> temp2;
    vector<double> temp3;
    vector<double> temp4;

    int N=ficheiro1.GetLines();

    for(int i=0;i<ficheiro1.GetLines();++i){
        for(int j =0;j<9;++j){
            temp1.push_back(atof(&(ficheiro1.GetData()[i][j][0])));
            temp2.push_back(atof(&(ficheiro2.GetData()[i][j][0])));
            temp3.push_back(atof(&(ficheiro3.GetData()[i][j][0])));
            temp4.push_back(atof(&(ficheiro4.GetData()[i][j][0])));
        }
        data1.push_back(temp1);
        data2.push_back(temp2);
        data3.push_back(temp3);
        data4.push_back(temp4);
        temp1.clear();
        temp2.clear();
        temp3.clear();
        temp4.clear();
    }

    vector<double> ang1;
    vector<double> ang2;
    vector<double> ang3;
    vector<double> ang4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        ang1.push_back(angconv(data1[i][0],data1[i][1],data1[i][2]));
        ang2.push_back(angconv(data2[i][0],data2[i][1],data2[i][2]));
        ang3.push_back(angconv(data3[i][0],data3[i][1],data3[i][2]));
        ang4.push_back(angconv(data4[i][0],data4[i][1],data4[i][2]));
        
        if(ang1[i]>300*(M_PI/180.))
        ang1[i]=ang1[i]-320*(M_PI/180.);
        else
        ang1[i]=(ang1[i]+360*(M_PI/180.))-320*(M_PI/180.);

        if(ang2[i]>300*(M_PI/180.))
        ang2[i]=ang2[i]-320*(M_PI/180.);
        else
        ang2[i]=(ang2[i]+360*(M_PI/180.))-320*(M_PI/180.);
    
        if(ang3[i]>75*(M_PI/180.))
        ang3[i]=70*(M_PI/180.)-(ang3[i]-360*(M_PI/180.));
        else
        ang3[i]=70*(M_PI/180.)-ang3[i];
        if(ang4[i]>75*(M_PI/180.))
        ang4[i]=70*(M_PI/180.)-(ang4[i]-360*(M_PI/180.));
        else
        ang4[i]=70*(M_PI/180.)-ang4[i];
    }

    vector<double> ref1;
    vector<double> ref2;
    vector<double> ref3;
    vector<double> ref4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        if(data1[i][8]==0) ref1.push_back(0); else ref1.push_back(((data1[i][6]+data1[i][7])/2.)/data1[i][8]);
        if(data2[i][8]==0) ref2.push_back(0); else ref2.push_back(((data2[i][6]+data2[i][7])/2.)/data2[i][8]);
        if(data3[i][8]==0) ref3.push_back(0); else ref3.push_back(((data3[i][6]+data3[i][7])/2.)/data3[i][8]);
        if(data4[i][8]==0) ref4.push_back(0); else ref4.push_back(((data4[i][6]+data4[i][7])/2.)/data4[i][8]);
    }

    vector<double> tra1;
    vector<double> tra2;
    vector<double> tra3;
    vector<double> tra4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        if(data1[i][5]==0) tra1.push_back(0); else tra1.push_back(((data1[i][3]+data1[i][4])/2.)/data1[i][5]);
        if(data2[i][5]==0) tra2.push_back(0); else tra2.push_back(((data2[i][3]+data2[i][4])/2.)/data2[i][5]);
        if(data3[i][5]==0) tra3.push_back(0); else tra3.push_back(((data3[i][3]+data3[i][4])/2.)/data3[i][5]);
        if(data4[i][5]==0) tra4.push_back(0); else tra4.push_back(((data4[i][3]+data4[i][4])/2.)/data4[i][5]);
    }

    TGraph G_tra1;
    TGraph G_tra2;
    TGraph G_tra3;
    TGraph G_tra4;
    TGraph G_ref1;
    TGraph G_ref2;
    TGraph G_ref3;
    TGraph G_ref4;
    for(int i=0; i<N;++i){
        //if(tra1[i]!=0)
            G_tra1.SetPoint(i,ang1[i],tra1[i]);
        //if(tra2[i]!=0)
            G_tra2.SetPoint(i,ang2[i],tra2[i]);
        //if(tra3[i]!=0)
            G_tra3.SetPoint(i,ang3[i],tra3[i]);
        //if(tra4[i]!=0)
            G_tra4.SetPoint(i,ang4[i],tra4[i]);
        //if(ref1[i]!=0)
            G_ref1.SetPoint(i,ang1[i],ref1[i]);
        //if(ref2[i]!=0)
            G_ref2.SetPoint(i,ang2[i],ref2[i]);
        //if(ref3[i]!=0)
            G_ref3.SetPoint(i,ang3[i],ref3[i]);
        //if(ref4[i]!=0)
            G_ref4.SetPoint(i,ang4[i],ref4[i]);
    }

    TCanvas* c1 = new TCanvas();



    auto lRefS = [](double *x,double *p=nullptr){
        return 0.181/0.0235*pow((p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2.);
    };

    TF1* fRefS= new TF1("L", lRefS, 0.,1.6,2);


    auto lRefP = [](double *x,double *p=nullptr){
        return .2105/0.0515*pow((p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };

    TF1* fRefP= new TF1("L", lRefP, 0.,1.6,2);



    auto lTransS = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*
        0.181/0.0235*
        p[1]/p[0]*
        sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*
        pow(1+(p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };

    TF1* fTransS= new TF1("L", lTransS, 0.,1.6,2);


    auto lTransP = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*p[1]/p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*pow(p[0]/p[1]*(1+(p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))),2);
    };

    TF1* fTransP= new TF1("L", lTransP, 0.,1.6,2);



    fTransS->SetParameter(0,1);
    fTransS->SetParameter(1,1.48);    
    fTransP->SetParameter(0,1);
    fTransP->SetParameter(1,1.48);    
    fRefP->SetParameter(0,1);
    fRefP->SetParameter(1,1.48);
    fRefS->SetParameter(0,1);
    fRefS->SetParameter(1,1.48);


    /*
    G_tra1.Fit(fTransS);
    G_tra1.Draw("AL");
    c1->SaveAs("tra1.png");
    c1->Clear();
    G_tra3.Fit(fTransP);
    G_tra3.Draw("AL");
    c1->SaveAs("tra3.png");
    c1->Clear();
    G_ref1.Fit(fRefS);
    G_ref1.Draw("AL");
    c1->SaveAs("ref1.png");
    c1->Clear();
    G_ref3.Fit(fRefP);
    G_ref3.Draw("AL");
    c1->SaveAs("ref3.png");
    c1->Clear();
*/

    G_tra1.Draw("AL");
    fTransS->Draw("same");
    c1->SaveAs("tra1.png");
    c1->Clear();
    G_tra3.Draw("AL");
    fTransP->Draw("same");
    c1->SaveAs("tra3.png");
    c1->Clear();
    G_ref1.Draw("AL");
    fRefS->Draw("same");
    c1->SaveAs("ref1.png");
    c1->Clear();
    G_ref3.Draw("AL");
    fRefP->Draw("same");
    c1->SaveAs("ref3.png");
    c1->Clear();






    auto lRefS1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*0.181/0.0235*pow((p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2.);
    //pow(({p*\cos(x)-p_{2}*\sqrt{1-\sin(x)*\sin(x)*(p/p_{2})*(p/p_{2})}}/{p*\cos(x)+p_{2}*\sqrt{1-\sin(x)*\sin(x)*(p/p_{2})*(p/p_{2})}}\right)^{2}0.181/0.0245\cdot\left(p\cdot p_{2}\cdot\frac{4}{\left(p+p_{2}\right)^{2}}),2)
    };
    TF1* fRefS1= new TF1("L", lRefS1, 0.,1.6,2);


    auto lRefP1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*pow((p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };
    TF1* fRefP1= new TF1("L", lRefP1, 0.,1.6,2);



    auto lTransS1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*
        0.181/0.0235*
        p[1]/p[0]*
        sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*
        pow(1+(p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };
    TF1* fTransS1= new TF1("L", lTransS1, 0.,1.6,2);


    auto lTransP1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*p[1]/p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*pow(p[0]/p[1]*(1+(p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))),2);
    };
    TF1* fTransP1= new TF1("L", lTransP1, 0.,1.6,2);



    fTransS1->SetParameter(0,1.48);
    fTransS1->SetParameter(1,1);
    fTransP1->SetParameter(0,1.48);
    fTransP1->SetParameter(1,1);    
    fRefP1->SetParameter(0,1.48);
    fRefP1->SetParameter(1,1);
    fRefS1->SetParameter(0,1.48);
    fRefS1->SetParameter(1,1.);



/*
    TAxis *ax_t = G_tra2.GetXaxis();
    TAxis *ay_t = G_tra2.GetYaxis();

    ax_t->SetLimits(0,1.6);
    ay_t->SetRangeUser(0,10);


    TAxis *ax_t1 = G_ref4.GetXaxis();
    TAxis *ay_t1 = G_ref4.GetYaxis();

    ax_t1->SetLimits(0,1.6);
    ay_t1->SetRangeUser(0,10);


    //G_tra2.Fit(fTransS1);
    G_tra2.Draw("AL");
    fTransS->Draw("same");
    c1->SaveAs("tra2.png");
    c1->Clear();
    G_tra4.Fit(fTransP1);
    G_tra4.Draw("AL");
    c1->SaveAs("tra4.png");
    c1->Clear();
    G_ref2.Fit(fRefS1);
    G_ref2.Draw("AL");
    c1->SaveAs("ref2.png");
    c1->Clear();
    G_ref4.Fit(fRefP1);
    G_ref4.Draw("AL");
    fRefP1->Draw("same");
    c1->SaveAs("ref4.png");
    c1->Clear();*/

    TGraph gTransS1,gTransP1,gRefS1,gRefP1;

    for(int i=0;i<1000000;i++){
        if(fTransS1->Eval(i*1.6/1000000)<10)
            gTransS1.SetPoint(i,i*1.6/1000000,fTransS1->Eval(i*1.6/1000000));

        if(fTransP1->Eval(i*1.6/1000000)<10)
            gTransP1.SetPoint(i,i*1.6/1000000,fTransP1->Eval(i*1.6/1000000));
        
        if(fRefS1->Eval(i*1.6/1000000)<10)
            gRefS1.SetPoint(i,i*1.6/1000000,fRefS1->Eval(i*1.6/1000000));
        
        if(fRefP1->Eval(i*1.6/1000000)<10)
            gRefP1.SetPoint(i,i*1.6/1000000,fRefP1->Eval(i*1.6/1000000));
//        cout<<i*1.6/1000000<<"   "<<fRefP1->Eval(i*1.6/10000)<<"   "<<fTransP1->Eval(i*1.6/10000)<<endl;
    }



    TMultiGraph* mult3= new TMultiGraph(); //mult3->SetTitle("Polarizacao S, Face C");
    TMultiGraph* mult4= new TMultiGraph(); //mult4->SetTitle("Polarizacao P, Face C");

    TMultiGraph* mult1= new TMultiGraph(); //mult1->SetTitle("Polarizacao S, Face P");
    TMultiGraph* mult2= new TMultiGraph(); //mult2->SetTitle("Polarizacao P, Face P");

    gStyle->SetOptFit(111);
    gStyle -> SetStatBorderSize(5);
    gStyle -> SetStatFontSize(1);
    gStyle -> SetStatFont(62);
    gStyle -> SetStatTextColor(1);
    gStyle -> SetStatColor(3);
    gStyle -> SetStatStyle(0);
    gStyle -> SetStatX(0.55);
    gStyle -> SetStatY(0.85);
    gStyle -> SetStatW(0.2165);
    gPad->SetGrid(1, 1); gPad->Update();



    TGraph LinhaS1;
    LinhaS1.SetPoint(0,0.74,7.17);
    LinhaS1.SetPoint(1,1.6,7.17);
    LinhaS1.SetLineColor(kRed); 
    LinhaS1.SetLineWidth(3);


    gRefS1.SetLineColor(kRed); 
    gRefS1.SetLineWidth(3);

    G_ref2.SetMarkerSize(1.5); 
    G_ref2.SetMarkerStyle(33);
    G_ref2.SetMarkerColor(kRed);
    G_ref2.Draw("AP");
    gRefS1.Draw("same");
    c1->SaveAs("ref2.png");
    c1->Clear();

    gTransS1.SetLineColor(kGreen); 
    gTransS1.SetLineWidth(3);

    G_tra2.SetMarkerSize(1.5); 
    G_tra2.SetMarkerStyle(33);
    G_tra2.SetMarkerColor(kGreen);

    G_tra2.Draw("APL");
    gTransS1.Draw("same");
    //fTransS1->Draw("same");
    c1->SaveAs("tra2.png");
    c1->Clear();

    mult3->Add(&G_ref2);
    mult3->Add(&gRefS1);
    mult3->Add(&G_tra2);
    mult3->Add(&gTransS1);
    mult3->Add(&LinhaS1);
    TAxis *ax1 = mult3->GetXaxis();
    TAxis *ay1 = mult3->GetYaxis();
    ax1->SetTitle("#theta (rad)");
    ay1->SetTitle("Potencia Recebida");
    ax1->SetLimits(0,1.6);
    ay1->SetRangeUser(0,10);
    mult3->Draw("APL");
    auto legend3 = new TLegend(0.5,0.8,0.9,0.9);
    legend3->SetTextFont(62);
    legend3->SetTextSize(0.03);
    legend3->AddEntry(&gRefS1,"P_{r}-Potencia refletida","l");
    legend3->AddEntry(&gTransS1,"P_{t}-Potencia transmitida","l");
    legend3->Draw("same");
    c1->SaveAs("PolS_FaceC.png");
    c1->Clear();

    TGraph LinhaS2;
    LinhaS2.SetPoint(0,0.74,3.75);
    LinhaS2.SetPoint(1,1.6,3.75);
    LinhaS2.SetLineColor(kRed); 
    LinhaS2.SetLineWidth(3);

    gTransP1.SetLineColor(kGreen); 
    gTransP1.SetLineWidth(3);

    G_tra4.SetMarkerSize(1.5); 
    G_tra4.SetMarkerStyle(33);
    G_tra4.SetMarkerColor(kGreen);
    G_tra4.Draw("APL");
    gTransP1.Draw("same");
    //fTransP1->Draw("same");
    //fRefS1->Draw("same");
    c1->SaveAs("tra4.png");
    c1->Clear();

    gRefP1.SetLineColor(kRed); 
    gRefP1.SetLineWidth(3);

    G_ref4.SetMarkerSize(1.5); 
    G_ref4.SetMarkerStyle(43);
    G_ref4.SetMarkerColor(kRed);

    G_ref4.Draw("APL");
    gRefP1.Draw("same");
    //fRefP1->Draw("same");
    c1->SaveAs("ref4.png");
    c1->Clear();

    mult4->Add(&G_ref4);
    mult4->Add(&gRefP1);
    mult4->Add(&G_tra4);
    mult4->Add(&gTransP1);
    mult4->Add(&LinhaS2);
    TAxis *ax2 = mult4->GetXaxis();
    TAxis *ay2 = mult4->GetYaxis();
    ax2->SetTitle("#theta (rad)");
    ay2->SetTitle("Potencia Recebida");
    ax2->SetLimits(0,1.5);
    ay2->SetRangeUser(0,6);
    mult4->Draw("APL");
    auto legend4 = new TLegend(0.5,0.8,0.9,0.9);
    legend4->SetTextFont(62);
    legend4->SetTextSize(0.03);
    legend4->AddEntry(&gRefP1,"P_{r}-Potencia refletida","l");
    legend4->AddEntry(&gTransP1,"P_{t}-Potencia transmitida","l");
    legend4->Draw("same");
    c1->SaveAs("PolP_FaceC.png");
    c1->Clear();

    fRefS->SetLineColor(kRed); 
    fRefS->SetLineWidth(3);

    G_ref1.SetMarkerSize(1.5); 
    G_ref1.SetMarkerStyle(33);
    G_ref1.SetMarkerColor(kRed);
    G_ref1.Draw("AP");
    fRefS->Draw("same");
    c1->SaveAs("ref1.png");
    c1->Clear();

    fTransS->SetLineColor(kGreen); 
    fTransS->SetLineWidth(3);

    G_tra1.SetMarkerSize(1.5); 
    G_tra1.SetMarkerStyle(33);
    G_tra1.SetMarkerColor(kGreen);

    G_tra1.Draw("APL");
    fTransS->Draw("same");
    //fTransS1->Draw("same");
    c1->SaveAs("tra1.png");
    c1->Clear();

    mult1->Add(&G_ref1);
    //mult1->Add(&fRefS);

    mult1->Add(&G_tra1);
    //mult1->Add(&fTransS);
    //mult1->Add(&LinhaS1);
    TAxis *ax11 = mult1->GetXaxis();
    TAxis *ay11 = mult1->GetYaxis();
    ax11->SetTitle("#theta (rad)");
    ay11->SetTitle("Potencia Recebida");
    ax11->SetLimits(0,1.6);
    ay11->SetRangeUser(0,10);
    mult1->Draw("APL");
    fRefS->Draw("same");
    fTransS->Draw("same");
    auto legend1 = new TLegend(0.5,0.8,0.9,0.9);
    legend1->SetTextFont(62);
    legend1->SetTextSize(0.03);
    legend1->AddEntry(&gRefS1,"P_{r}-Potencia refletida","l");
    legend1->AddEntry(&gTransS1,"P_{t}-Potencia transmitida","l");
    legend1->Draw("same");
    c1->SaveAs("PolS_FaceP.png");
    c1->Clear();
/////////

    fRefP->SetLineColor(kRed); 
    fRefP->SetLineWidth(3);

    G_ref3.SetMarkerSize(1.5); 
    G_ref3.SetMarkerStyle(33);
    G_ref3.SetMarkerColor(kRed);
    G_ref3.Draw("AP");
    fRefP->Draw("same");
    c1->SaveAs("ref1.png");
    c1->Clear();

    fTransP->SetLineColor(kGreen); 
    fTransP->SetLineWidth(3);

    G_tra3.SetMarkerSize(1.5); 
    G_tra3.SetMarkerStyle(33);
    G_tra3.SetMarkerColor(kGreen);

    G_tra3.Draw("APL");
    fTransP->Draw("same");
    //fTransS1->Draw("same");
    c1->SaveAs("tra1.png");
    c1->Clear();

    mult2->Add(&G_ref3);
    //mult1->Add(&fRefS);

    mult2->Add(&G_tra3);
    //mult1->Add(&fTransS);
    //mult1->Add(&LinhaS1);
    TAxis *ax22 = mult2->GetXaxis();
    TAxis *ay22 = mult2->GetYaxis();
    ax22->SetTitle("#theta (rad)");
    ay22->SetTitle("Potencia Recebida");
    ax22->SetLimits(0,1.6);
    ay22->SetRangeUser(0,6);
    mult2->Draw("APL");
    fRefP->Draw("same");
    fTransP->Draw("same");
    auto legend22 = new TLegend(0.5,0.8,0.9,0.9);
    legend22->SetTextFont(62);
    legend22->SetTextSize(0.03);
    legend22->AddEntry(&gRefS1,"P_{r}-Potencia refletida","l");
    legend22->AddEntry(&gTransS1,"P_{t}-Potencia transmitida","l");
    legend22->Draw("same");
    c1->SaveAs("PolP_FaceP.png");
    c1->Clear();

    return 0;
}