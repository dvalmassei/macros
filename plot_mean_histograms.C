void plot_mean_histograms(vector<TString> file_list, TString tree_name, TString var_name) {

  // Create a TChain to hold all the trees from the filesplt
  TChain *chain = new TChain(tree_name);
  for (TString file : file_list) {
    chain->Add(file);
  }

  // Create a TH1D histogram for each file
  vector<TH1D*> hist_list;
  for (int i=0; i<file_list.size(); i++) {
    TString hist_name = Form("hist_%d", i);
    TString draw_command = Form("%s>>%s", var_name.Data(), hist_name.Data());
    TH1D *hist = new TH1D(hist_name, "", 100, 0, 10);
    chain->Draw(draw_command, "", "goff");
    hist->SetDirectory(0);
    hist_list.push_back(hist);
  }

  // Create a TGraphErrors to hold the mean and standard deviation of each histogram
  TGraphErrors *graph = new TGraphErrors();
  for (int i=0; i<hist_list.size(); i++) {
    double mean = hist_list[i]->GetMean();
    double std_dev = hist_list[i]->GetStdDev();
    graph->SetPoint(i, i, mean);
    graph->SetPointError(i, 0, std_dev);
  }

  // Create a canvas and draw the graph
  TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
  graph->SetTitle("Mean Histograms");
  graph->GetXaxis()->SetTitle("File Index");
  graph->GetYaxis()->SetTitle("Mean of Histogram");
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1.5);
  graph->Draw("AP");

  // Cleanup
  for (TH1D* hist : hist_list) {
    delete hist;
  }
  delete chain;
  delete graph;
}
