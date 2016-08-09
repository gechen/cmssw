# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: validation -s VALIDATION:genvalid_all --conditions auto:run2_mc --magField 38T_PostLS1 --beamspot Realistic50ns13TeVCollision --geometry Extended2023LReco --datatier GEN-SIM-DIGI --eventcontent FEVTDEBUGHLT ^Scustomise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023LReco -n -1 --no_exec --filein file:out_reco.root --fileout file:out_valid.root --python_filename=valid_test.py --era Phase2LReco
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('VALIDATION',eras.Phase2LReco)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023simReco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Validation_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		 'file:out_reco.root',
	 ),
    secondaryFileNames = cms.untracked.vstring(
	 )
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('validation nevts:-1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(10485760),
    fileName = cms.untracked.string('file:out_valid.root'),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.mix.playback = True
process.mix.digitizers = cms.PSet()
for a in process.aliases: delattr(process, a)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

# Path and EndPath definitions
process.validation_step = cms.EndPath(process.gemSimValid)
#process.validation_step = cms.EndPath(process.gemSimValid+process.me0SimValid)
#process.validation_step = cms.EndPath(process.genvalid_all)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.validation_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

# customisation of the process.
# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023LReco 

#call to customisation function cust_2023LReco imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023LReco(process)

# Automatic addition of the customisation function from SimGeneral.MixingModule.fullMixCustomize_cff
from SimGeneral.MixingModule.fullMixCustomize_cff import setCrossingFrameOn 

#call to customisation function setCrossingFrameOn imported from SimGeneral.MixingModule.fullMixCustomize_cff
process = setCrossingFrameOn(process)

# End of customisation functions

process.gemSimHitValidation.detailPlot = cms.bool(True)
process.gemSimTrackValidation.detailPlot = cms.bool(True)
process.gemStripValidation.detailPlot = cms.bool(True)
process.gemPadValidation.detailPlot = cms.bool(True)
process.gemCoPadValidation.detailPlot = cms.bool(True)
process.gemDigiTrackValidation.detailPlot = cms.bool(True)
process.gemGeometryChecker.detailPlot = cms.bool(True)
process.gemRecHitsValidation.detailPlot = cms.bool(True)
process.gemRecHitTrackValidation.detailPlot = cms.bool(True)

