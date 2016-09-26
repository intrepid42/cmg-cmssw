#ifndef HcalSimHitsValidation_H
#define HcalSimHitsValidation_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalSourcePositionData.h"

#include <DataFormats/EcalDetId/interface/EBDetId.h>
#include <DataFormats/EcalDetId/interface/EEDetId.h>
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/HcalDetId/interface/HcalElectronicsId.h"
#include "Geometry/HcalCommonData/interface/HcalDDDRecConstants.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"

#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include <vector>
#include <utility>
#include <ostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "DQMServices/Core/interface/MonitorElement.h"


class HcalSimHitsValidation : public DQMEDAnalyzer {

public:
  HcalSimHitsValidation(edm::ParameterSet const& conf);
  ~HcalSimHitsValidation();

  virtual void bookHistograms(DQMStore::IBooker &, edm::Run const &, edm::EventSetup const & );

  virtual void analyze(edm::Event const& ev, edm::EventSetup const& c);
  virtual void endJob() ;

private:
  
  double dR(double eta1, double phi1, double eta2, double phi2);
  double phi12(double phi1, double en1, double phi2, double en2);
  double dPhiWsign(double phi1,double phi2);  

  std::string outputFile_;

  edm::EDGetTokenT<edm::HepMCProduct> tok_evt_;
  edm::EDGetTokenT<edm::PCaloHitContainer> tok_hcal_;
  edm::EDGetTokenT<edm::PCaloHitContainer> tok_ecalEB_;
  edm::EDGetTokenT<edm::PCaloHitContainer> tok_ecalEE_;

  const HcalDDDRecConstants               *hcons;
  int                                      maxDepthHB_, maxDepthHE_;
  int                                      maxDepthHO_, maxDepthHF_;


  // Hits counters
  std::vector<MonitorElement*> Nhb;
  std::vector<MonitorElement*> Nhe;
  MonitorElement* Nho;
  std::vector<MonitorElement*> Nhf;

  // In ALL other cases : 2D ieta-iphi maps 
  // without and with cuts (a la "Scheme B") on energy
  // - only in the cone around particle for single-part samples (mc = "yes")
  // - for all calls in milti-particle samples (mc = "no")

  std::vector<MonitorElement*> emean_vs_ieta_HB;
  std::vector<MonitorElement*> emean_vs_ieta_HE;
  MonitorElement* emean_vs_ieta_HO;
  std::vector<MonitorElement*> emean_vs_ieta_HF;

  std::vector<MonitorElement*> occupancy_vs_ieta_HB;
  std::vector<MonitorElement*> occupancy_vs_ieta_HE;
  MonitorElement* occupancy_vs_ieta_HO;
  std::vector<MonitorElement*> occupancy_vs_ieta_HF;

  // for single monoenergetic particles - cone collection profile vs ieta.
  MonitorElement* meEnConeEtaProfile;
  MonitorElement* meEnConeEtaProfile_E;
  MonitorElement* meEnConeEtaProfile_EH;

  // energy of rechits
  std::vector<MonitorElement*> meSimHitsEnergyHB;
  std::vector<MonitorElement*> meSimHitsEnergyHE;
  MonitorElement* meSimHitsEnergyHO;
  std::vector<MonitorElement*> meSimHitsEnergyHF;

  edm::ESHandle<CaloGeometry> geometry ;

  // counter
  int nevtot;

};

#endif
