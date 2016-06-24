#include "CalibTracker/SiStripCommon/interface/ShallowEventDataProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

ShallowEventDataProducer::ShallowEventDataProducer(const edm::ParameterSet& iConfig) {
  produces <unsigned int> ( "run"      );
  produces <unsigned int> ( "event"    );
  produces <unsigned int> ( "bx"       );
  produces <unsigned int> ( "lumi"       );
  produces <std::vector<bool> > ( "TrigTech" );
  produces <std::vector<bool> > ( "TrigPh" );
	trig_token_ = consumes<L1GlobalTriggerReadoutRecord>(
		iConfig.getParameter<edm::InputTag>("trigRecord")
		);
}

void ShallowEventDataProducer::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {


  auto run   = std::make_unique<unsigned int>(iEvent.id().run()   );
  auto event = std::make_unique<unsigned int>(iEvent.id().event() );
  auto bx    = std::make_unique<unsigned int>(iEvent.bunchCrossing() );
  auto lumi  = std::make_unique<unsigned int>(iEvent.luminosityBlock() );


  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByToken(trig_token_, gtRecord);

  std::vector<bool> TrigTech_(64,0);
  std::vector<bool> TrigPh_(128,0);

  // Get dWord after masking disabled bits
  DecisionWord dWord = gtRecord->decisionWord();
  if ( ! dWord.empty() ) { // if board not there this is zero
    // loop over dec. bit to get total rate (no overlap)
    for ( int i = 0; i < 64; ++i ) {
      TrigPh_[i]= dWord[i];
    }
  }
    
  TechnicalTriggerWord tw = gtRecord->technicalTriggerWord();
  if ( ! tw.empty() ) {
    // loop over dec. bit to get total rate (no overlap)
    for ( int i = 0; i < 64; ++i ) {
      TrigTech_[i]=tw[i];
    }
  }

  auto TrigTech = std::make_unique<std::vector<bool>>(TrigTech_);
  auto TrigPh = std::make_unique<std::vector<bool>>(TrigPh_);

  iEvent.put(std::move(run),      "run"   );
  iEvent.put(std::move(event),    "event" );
  iEvent.put(std::move(bx),       "bx" );
  iEvent.put(std::move(lumi),       "lumi" );
  iEvent.put(std::move(TrigTech), "TrigTech" );
  iEvent.put(std::move(TrigPh),   "TrigPh" );
}
