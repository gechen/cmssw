from RecoPixelVertexing.PixelTriplets.pixelTripletLargeTipEDProducerDefault_cfi import pixelTripletLargeTipEDProducerDefault as _pixelTripletLargeTipEDProducerDefault

pixelTripletLargeTipEDProducer = _pixelTripletLargeTipEDProducerDefault.clone()
from Configuration.Eras.Modifier_trackingLowPU_cff import trackingLowPU
from Configuration.Eras.Modifier_trackingPhase1PU70_cff import trackingPhase1PU70
from Configuration.Eras.Modifier_trackingPhase2PU140_cff import trackingPhase2PU140
trackingLowPU.toModify(pixelTripletLargeTipEDProducer, maxElement=100000)
trackingPhase1PU70.toModify(pixelTripletLargeTipEDProducer, maxElement=0)
trackingPhase2PU140.toModify(pixelTripletLargeTipEDProducer, maxElement=0)

from Configuration.Eras.Modifier_peripheralPbPb_cff import peripheralPbPb
peripheralPbPb.toModify(pixelTripletLargeTipEDProducer, maxElement=1000000)
