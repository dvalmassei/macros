void yield_rate(TString Ebeam = "E887MeV"){
    const int Qtor[] = {600};
    const int nQtor = sizeof(Qtor)/sizeof(*Qtor);
    TH1D* hPEforRate[nQtor];
    TH1D* hPEforYield[nQtor];
    TH1D* hPEforEnergy[nQtor];
    TH1D* hPEforTheta[nQtor];
    TH1D* hPEforPhi[nQtor];


    /////////////// Set Up Workdir and Output Files ///////////////
    const TString rootfile_dir = Form("/lustre19/expphy/volatile/hallc/qweak/adhidevi/rootfiles/E887MeV/Oct7_EV1111_d_BEAM_QTOR600");
    ofstream fout(Form("./textfiles/%s/%s.csv",Ebeam.Data(),Ebeam.Data()));
    fout<<Form("%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s",
        "QTOR","Rate_Mean","Rate_RMS","Rate_Entries","Yield_Mean","Yield_RMS","Yield_Entries",
        "Energy_Mean","Energy_RMS","Energy_Entries","Theta_Mean","Theta_RMS","Theta_Entries","Phi_Mean","Phi_RMS","Phi_Entries")<<endl;
    // this is a storage file for all the data (I think)//
    TFile* ofile = new TFile(Form("./rootfiles/%s/%s_All.root",Ebeam.Data(),Ebeam.Data()),"RECREATE");

    /////////////// Analyze Rootfiles ///////////////
    for(int iQtor=0;iQtor<nQtor;iQtor++){
        TChain* T = new TChain("QweakSimG4_Tree");

        // Add Rootfiles to One Tree //
        for(int iRun=1001;iRun=<6000;iRun++){
            T->Add(Form("%s/Oct7_EV1111_d_BEAM_QTOR600_%d.root",rootfile_dir.Data(),iRun));
        }

        // Write Number of Entries in Combined Tree out to Console //
        Int_t nentry = T->GetEntries();
        cout<<Form("QTOR: %d \t Entries: %d",Qtor[iQtor],nentry)<<endl;


        // Set Up Canvas //
        TCanvas* c1 = new TCanvas(Form("c%d",iQtor),Form("c%d",iQtor),1100,1500);
        c1->Divide(2,3);


        // Draw Rate Histogram in first section of the Canvas //
        c1->cd(1);
        T->Draw(Form("Cerenkov.PMT.PMTTotalRate[7]>>Rate_QTOR%d",Qtor[iQtor]),"Cerenkov.PMT.PMTLeftNbOfPEs[7]>0 && Cerenkov.PMT.PMTRightNbOfPEs[7]>0","goff");
        
        // Draw Rate Histogram in the combined rate histogram //
        hPEforRate[iQtor] = (TH1D*)gDirectory->FindObject(Form("Rate_QTOR%d",Qtor[iQtor]));
        hPEforRate[iQtor]->SetDirectory(gROOT);
        hPEforRate[iQtor]->SetTitle(Form("%d PMTTotalRate[7] {PMTLeftNbOfPEs[7]>0 && PMTRightNbOfPEs[7]>0};PMTTotalRate[7];Events",Qtor[iQtor]));
        hPEforRate[iQtor]->Draw("hist");
        hPEforRate[iQtor]->Write();

        // Draw Yield Histogram in second section of the Canvas //
        c1->cd(2);
        T->Draw(Form("Cerenkov.PMT.PMTTotalYield[7]>>Yield_QTOR%d",Qtor[iQtor]),"Cerenkov.PMT.PMTTotalNbOfPEs[7]>0","goff");

        // Draw Yield Histogram in the combined rate histogram //
        hPEforYield[iQtor] = (TH1D*)gDirectory->FindObject(Form("Yield_QTOR%d",Qtor[iQtor]));
        hPEforYield[iQtor]->SetDirectory(gROOT);
        hPEforYield[iQtor]->SetTitle(Form("%d PMTTotalYield[7] {PMTTotalNbOfPEs[7]>0};PMTTotalYield[7];Events",Qtor[iQtor]));
        hPEforYield[iQtor]->Draw("hist");
        hPEforYield[iQtor]->Write();

        // Draw Energy Histogram in third section of the Canvas //
        c1->cd(3);
        T->Draw(Form("Primary.OriginVertexKineticEnergy>>Energy_QTOR%d",Qtor[iQtor]),"Cerenkov.PMT.PMTTotalNbOfPEs[7]>0","goff");

        // Draw Energy Histogram in the combined rate histogram //
        hPEforEnergy[iQtor] = (TH1D*)gDirectory->FindObject(Form("Energy_QTOR%d",Qtor[iQtor]));
        hPEforEnergy[iQtor]->SetDirectory(gROOT);
        hPEforEnergy[iQtor]->SetTitle(Form("%d KineticEnergy[7] {PMTTotalNbOfPEs[7]>0};Kinetic Energy[7];Events",Qtor[iQtor]));
        hPEforEnergy[iQtor]->Draw("hist");
        hPEforEnergy[iQtor]->Write();


        // Draw Theta Histogram in third section of the Canvas //
        c1->cd(4);
        T->Draw(Form("Primary.OriginVertexThetaAngle>>Theta_QTOR%d",Qtor[iQtor]),"Cerenkov.PMT.PMTTotalNbOfPEs[7]>0","goff");

        // Draw Theta Histogram in the combined rate histogram //
        hPEforTheta[iQtor] = (TH1D*)gDirectory->FindObject(Form("Theta_QTOR%d",Qtor[iQtor]));
        hPEforTheta[iQtor]->SetDirectory(gROOT);
        hPEforTheta[iQtor]->SetTitle(Form("%d ThetaAngle[7] {PMTTotalNbOfPEs[7]>0};Theta[7];Events",Qtor[iQtor]));
        hPEforTheta[iQtor]->Draw("hist");
        hPEforTheta[iQtor]->Write();

        // Draw Phi Histogram in third section of the Canvas //
        c1->cd(5);
        T->Draw(Form("Primary.OriginVertexPhiAngle>>Phi_QTOR%d",Qtor[iQtor]),"Cerenkov.PMT.PMTTotalNbOfPEs[7]>0","goff");

        // Draw Phi Histogram in the combined rate histogram //
        hPEforPhi[iQtor] = (TH1D*)gDirectory->FindObject(Form("Phi_QTOR%d",Qtor[iQtor]));
        hPEforPhi[iQtor]->SetDirectory(gROOT);
        hPEforPhi[iQtor]->SetTitle(Form("%d PhiAngle[7] {PMTTotalNbOfPEs[7]>0};Phi[7];Events",Qtor[iQtor]));
        hPEforPhi[iQtor]->Draw("hist");
        hPEforPhi[iQtor]->Write();

        // Write data to csv, then to console //
        fout<<Form("%d, %.5e, %.5e, %.0f, %.5e, %.5e, %.0f, %.5e, %.5e, %.0f, %.5e, %.5e, %.0f, %.5e, %.5e, %.0f, %d",
            Qtor[iQtor],hPEforRate[iQtor]->GetMean(),hPEforRate[iQtor]->GetRMS(),hPEforRate[iQtor]->GetEntries(),
            hPEforYield[iQtor]->GetMean(),hPEforYield[iQtor]->GetRMS(),hPEforYield[iQtor]->GetEntries(),
            hPEforEnergy[iQtor]->GetMean(),hPEforEnergy[iQtor]->GetRMS(),hPEforEnergy[iQtor]->GetEntries(),
            hPEforTheta[iQtor]->GetMean(),hPEforTheta[iQtor]->GetRMS(),hPEforTheta[iQtor]->GetEntries(),
            hPEforPhi[iQtor]->GetMean(),hPEforPhi[iQtor]->GetRMS(),hPEforPhi[iQtor]->GetEntries(),nentry)<<endl;
        cout<<Form("%d \t %.5e \t %.5e \t %.0f \t %.5e \t %.5e \t %.0f \t %.5e \t %.5e \t %.0f \t %d",
            Qtor[iQtor],hPEforRate[iQtor]->GetMean(),hPEforRate[iQtor]->GetRMS(),hPEforRate[iQtor]->GetEntries(),
            hPEforYield[iQtor]->GetMean(),hPEforYield[iQtor]->GetRMS(),hPEforYield[iQtor]->GetEntries(),
            hPEforEnergy[iQtor]->GetMean(),hPEforEnergy[iQtor]->GetRMS(),hPEforEnergy[iQtor]->GetEntries(),nentry)<<endl;
        
        // SAVE PLOTS!!! //
        c1->SaveAs(Form("./plots/%s/temp/PEplot_%d.pdf",Ebeam.Data(),Qtor[iQtor]));

    }

    // Don't forget to close your files //
    fout.close();
    ofile->Close();

    // Clean up //
    gSystem->Exec(Form("pdfunite ./plots/%s/temp/PEplot_*.pdf ./plots/%s.pdf",Ebeam.Data(),Ebeam.Data()));
    gSystem->Exec(Form("rm -rf ./plots/%s/temp/PEplot_*.pdf",Ebeam.Data()));

}