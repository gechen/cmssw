/*  Derived from DTGeometryAnalyzer by Nicola Amapane
 *  based on M. Maggi - INFN Bari
 *  \author Geng CHEN - PKU, CN
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartitionSpecs.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include <memory>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>

class ME0GeometryAnalyzer : public edm::one::EDAnalyzer<>
{
public: 
  ME0GeometryAnalyzer( const edm::ParameterSet& pset);

  ~ME0GeometryAnalyzer();

  void beginJob() override {}
  void analyze(edm::Event const& iEvent, edm::EventSetup const&) override;
  void endJob() override {}
  
private:
  const std::string& myName() { return myName_;}

  const int dashedLineWidth_;
  const std::string dashedLine_;
  const std::string myName_;
  std::ofstream ofos;
};

using namespace std;

ME0GeometryAnalyzer::ME0GeometryAnalyzer( const edm::ParameterSet& /*iConfig*/ )
  : dashedLineWidth_(104), dashedLine_( string(dashedLineWidth_, '-') ), 
    myName_( "ME0GeometryAnalyzer" ) 
{ 
  ofos.open("ME0HTMLtestOutput_27_04.html"); 
  ofos <<"<!DOCTYPE html>"<< endl;
  ofos <<"<html>"<< endl;
  ofos << "<head>" << endl << "<style>" << endl << "   table, th, td {" << endl << " border: 1px solid black;" << endl << " border-collapse: collapse;"<< endl << " }" << endl << " th {" << endl << "  padding: 5x;" << endl << "   text-align: center; " << endl << "color:red;" << endl << "font-size:160%;}" << endl <<  " td { " << endl << "  padding: 5px;" << endl <<"   text-align: center; "<< endl << " } " << endl << "</style>" << endl;
  ofos << "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>" << endl;
  ofos << "<script>" << endl
       << " $(document).ready(function(){" << endl
       << " $(\"#hide\").click(function(){" << endl
       << "  $(\"table\").hide();" << endl
       << "});" << endl
       << "     $(\"#show\").click(function(){" << endl
       << "  $(\"table\").show();" << endl
       << " });" << endl
       << " });" << endl
       << "</script>" << endl;
  ofos << "</head>" <<endl;
  ofos <<"<body>"<< endl; 
  ofos <<"<p1> ======================== Opening output file </p1>"<< endl;
}

ME0GeometryAnalyzer::~ME0GeometryAnalyzer() 
{
  ofos.close();
  ofos <<"======================== Closing output file"<< endl;
}

void
ME0GeometryAnalyzer::analyze( const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup )
{
  edm::ESHandle<ME0Geometry> pDD;
  iSetup.get<MuonGeometryRecord>().get(pDD);     
  
  ofos << myName() << ": Analyzer..." << endl;
  ofos << "start " << dashedLine_ << endl;

  ofos << " Geometry node for ME0Geom is  " << &(*pDD) << endl;   
  ofos << " detTypes       \t"              <<pDD->detTypes().size() << endl;
  ofos << " GeomDetUnit       \t"           <<pDD->detUnits().size() << endl;
  ofos << " GeomDet           \t"           <<pDD->dets().size() << endl;
  ofos << " GeomDetUnit DetIds\t"           <<pDD->detUnitIds().size() << endl;
  ofos << " eta partitions \t"              <<pDD->etaPartitions().size() << endl;

  ofos << " chambers       \t"              <<pDD->chambers().size() << endl;
  ofos << " super chambers  \t"             <<pDD->superChambers().size() << endl;
  ofos << " rings  \t\t"                    <<pDD->rings().size() << endl;
  ofos << " stations  \t\t"                 <<pDD->stations().size() << endl;
  ofos << " regions  \t\t"                  <<pDD->regions().size() << endl;
  
  // checking uniqueness of roll detIds 
  bool flagNonUniqueRollID = false;
  bool flagNonUniqueRollRawID = false;
  int nstrips = 0;
  int npads = 0;
  for (auto roll1 : pDD->etaPartitions()){
    nstrips += roll1->nstrips();
    npads += roll1->npads();
    for (auto roll2 : pDD->etaPartitions()){
      if (roll1 != roll2){
	if (roll1->id() == roll2->id()) flagNonUniqueRollID = true;
	if (roll1->id().rawId() == roll2->id().rawId()) flagNonUniqueRollRawID = true;
      }
    }
  }
  // checking the number of strips and pads
  ofos << " total number of strips\t"<<nstrips << endl;
  ofos << " total number of pads  \t"<<npads << endl;
  if (flagNonUniqueRollID or flagNonUniqueRollRawID)
    ofos << " -- WARNING: non unique roll Ids!!!" << endl;

  // checking uniqueness of chamber detIds
  bool flagNonUniqueChID = false;
  bool flagNonUniqueChRawID = false;
  for (auto ch1 : pDD->chambers()){
    for (auto ch2 : pDD->chambers()){
      if (ch1 != ch2){
	if (ch1->id() == ch2->id()) flagNonUniqueChID = true;
	if (ch1->id().rawId() == ch2->id().rawId()) flagNonUniqueChRawID = true;
      }
    }
  }
  if (flagNonUniqueChID or flagNonUniqueChRawID)
    ofos << " -- WARNING: non unique chamber Ids!!!" << endl;

  ofos << myName() << ": Begin iteration over geometry..." << endl;
  ofos << "iter " << dashedLine_ << endl;
  
  ofos << myName() << "Begin ME0Geometry TEST" << endl;
  ofos<<"<table style=\"width:100%\">" << endl << "<tr>" << endl;
  ofos << "<th> ME0 Super Chamber Id </th>" << endl << "<th> Chamber </th>" << endl << "<th> Roll </th>" << endl << "<th> r (bottom) in cm </th>" << endl << "<th> W in cm </th>" << endl << "<th> h in cm </th>" << endl << "<th> cStrip1 phi </th>"<< endl << "<th> cStripN phi </th>"<< endl << "<th> dphi </th>"<< endl << "<th> global Z </th>"<< endl << "</tr>" << endl;
  
  for (auto region : pDD->regions()) {
    for (auto station : region->stations()) {
      for (auto ring : station->rings()) {
	int i = 1;
	for (auto sch : ring->superChambers()) {
	  GEMDetId schId(sch->id());
	  ofos << "<tr>" << endl;
	  ofos << "<td>" << schId << "</td>" << endl;
	  // checking the dimensions of each partition & chamber
	  int j = 1;
	  for (auto ch : sch->chambers()){
	    GEMDetId chId(ch->id());
	      int nRolls(ch->nEtaPartitions());
	    ofos << "<td>" << j << "</td>" << endl;
	    int k = 1;
	    auto& rolls(ch->etaPartitions());
	    for (auto roll : rolls){
	      ofos << "<td>" << k << "</td>" << endl;	      
	      const BoundPlane& bSurface(roll->surface());
	      const StripTopology* topology(&(roll->specificTopology()));
	      
	      // base_bottom, base_top, height, strips, pads (all half length)
	      auto& parameters(roll->specs()->parameters());
	      float bottomEdge(parameters[0]);
	      //  float topEdge(parameters[1]);
	      float height(parameters[2]);
	      float nStrips(parameters[3]);
	      //  float nPads(parameters[4]);
	      
	       LocalPoint  lCentre( 0., 0., 0. );
	      GlobalPoint gCentre(bSurface.toGlobal(lCentre));
	      LocalPoint  lBottom( 0., -height, 0.);
	      GlobalPoint gBottom(bSurface.toGlobal(lBottom));
	      double cz(gCentre.z());
	      double bx(gBottom.x());
	      double by(gBottom.y());
	      // print info about edges
	      LocalPoint lEdge1(topology->localPosition(0.));
	      LocalPoint lEdgeN(topology->localPosition((float)nStrips));
	      
	      double cstrip1(roll->toGlobal(lEdge1).phi().degrees());
	      double cstripN(roll->toGlobal(lEdgeN).phi().degrees());
	      double dphi(fabs(cstripN - cstrip1));
	      if (dphi > 180.) dphi = (360.- dphi);

	      //double deta(abs(beta - teta));
	      const bool printDetails(true);
	      if (printDetails) {
		ofos //<< "|    \t\tType: " << type << endl
		  << "<td>" << std::sqrt(bx*bx + by*by) << "</td>" << endl << "<td>" << bottomEdge*2 << "</td>" << endl << "<td>" << height*2 << "</td> " << endl
		  << "<td>" << cstrip1 << " </td>" << endl<< "<td>" << cstripN << " </td>" << endl << "<td>" << dphi << "</td>" << endl << "<td>" << cz << "</td>" << endl << "</tr>" << endl;
	      }
	      if(k<=nRolls)ofos << "<tr>" << endl<< "<td> </td>" << endl<< "<td> </td>" << endl;
	      ++k;
	    }
	    if(j <= sch->nChambers()) ofos << "<tr>" << endl << "<td> </td>" << endl;
	    ++j;
	  }
	  ++i;
	}
      }
    }
  }
	    
  ofos << "</table>" << endl;
  ofos << "<button id=\"hide\">Hide</button>" << endl;
  ofos << "<button id=\"show\">Show</button>" << endl;
  ofos << "<p>" <<  dashedLine_ << " end </p>" << endl << "</body>" << endl << "</html>" << endl;

}

//define this as a plug-in
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(ME0GeometryAnalyzer);
