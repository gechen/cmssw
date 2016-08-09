# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleMuPt100_cfi -s GEN,SIM --conditions auto:run2_mc --magField 38T_PostLS1 --beamspot Realistic50ns13TeVCollision --datatier GEN-SIM --geometry Extended2023LReco --eventcontent FEVTDEBUG --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023LReco -n 10 --no_exec --fileout out_sim.root --python_filename SingleMuPt100_test.py --era Phase2
#import CondCore.CondDB.CondDB_cfi as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Phase2LReco)

# import of standard configurations
#process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023simReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023sim_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('SingleMuPt100_cfi nevts:2000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('out_sim.root'),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.generator = cms.EDProducer("FlatRandomPtGunProducer",
    AddAntiParticle = cms.bool(True),
    PGunParameters = cms.PSet(
        MaxEta = cms.double(2.5),
        MaxPhi = cms.double(3.14159265359),
        MaxPt = cms.double(100.01),
        MinEta = cms.double(-2.5),
        MinPhi = cms.double(-3.14159265359),
        MinPt = cms.double(99.99),
        PartID = cms.vint32(-13)
    ),
    Verbosity = cms.untracked.int32(0),
    firstRun = cms.untracked.uint32(1),
    psethack = cms.string('single mu pt 100')
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.FEVTDEBUGoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023LReco 

#call to customisation function cust_2023LReco imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023LReco(process)

# End of customisation functions



# , CondCore.DBCommon.CondDBSetup_cfi.CondDBSetup , connect = cms.sqlite_file:/afs/cern.ch/work/t/tosi/public/DQM/checkDB/CMSSW_8_0_4/src/DQM/TrackerCommon/test/AlCaRecoTriggerBits_TrackerDQM. ) , toGet = cms.VPSet( cms.PSet( record = cms. ) , tag = cms.AlCaRecoTriggerBits_TrackerDQM_ ) , label = cms.untracked. ) ) ) ) process.es_prefer = )

#import CondCore.DBCommon.CondDBSetup_cfi process.dbInput = cms. , CondCore.DBCommon.CondDBSetup_cfi.CondDBSetup , connect = cms.sqlite_file:/afs/cern.ch/work/t/tosi/public/DQM/checkDB/CMSSW_8_0_4/src/DQM/TrackerCommon/test/AlCaRecoTriggerBits_TrackerDQM. ) , toGet = cms.VPSet( cms.PSet( record = cms. ) , tag = cms.AlCaRecoTriggerBits_TrackerDQM_ ) , label = cms.untracked. ) ) ) ) process.es_prefer = )

#dbInputcms.,PoolDBESSourceESPrefer(SiStripDQMTriggerstring( v1string( AlCaRecoTriggerBitsRcdstring( dbstring( PoolDBESSourceESSource( 
