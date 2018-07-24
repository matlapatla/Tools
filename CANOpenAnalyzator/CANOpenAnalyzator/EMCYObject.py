
class EMCYObject:
    'Common class for the CANOpen Emcy write'
    EMCYObjectCount = 0
    def __init__ (self, CANID, TimeOffset, eec = -1, er = -1, msef = -1):
        self.CANID = CANID
        self.eec = eec
        self.er = er
        self.msef = msef
        self.NodeID = int(self.CANID,16) - 128
        self.TimeOffset = TimeOffset
        EMCYObject.EMCYObjectCount += 1

        self.operationalStateCount = 0

    def DisplayDecoded(self):
       
            print (self.TimeOffset + "-!- EMCY write " + "CAN-ID %d" + "Node-ID %d" % int(self.CANID,16), self.NodeID)
            
        