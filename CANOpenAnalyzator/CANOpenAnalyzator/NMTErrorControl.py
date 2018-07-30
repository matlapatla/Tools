class NMTErrorControl:
    'Common class for the CANOpen NMT Error Control'
    NMTErrorControlCount = 0
    def __init__ (self, CANID, r, s, TimeOffset):
        self.CANID = CANID
        self.r = r
        self.s = s
        self.NodeID = int(self.CANID,16) - 1792
        self.TimeOffset = TimeOffset
        NMTErrorControl.NMTErrorControlCount += 1

        self.operationalStateCount = 0

    def DisplayDecoded(self):
        if (self.s == "00"):
            print (self.TimeOffset + "NMTErrorControl Boot-up " + "Node-ID = %d" % self.NodeID)
            self.operationalStateCount = 0
        elif (self.s == "04"):
            print (self.TimeOffset + "NMTErrorControl Stopped " + "Node-ID = %d" % self.NodeID)
            self.operationalStateCount = 0
        elif (self.s == "05"): 
            self.operationalStateCount += 1
            #if (self.operationalStateCount == 1):
            #print (self.TimeOffset + "NMTErrorCtrl Operational " + "Node-ID = %d" % self.NodeID + " operationalStateCount = " + str(self.operationalStateCount))
            print (self.TimeOffset + "NMTErrorCtrl Operational " + "Node-ID = %d" % self.NodeID)
        elif (self.s == "7F"): #127
            print (self.TimeOffset + "NMTErrorControl Pre-operational " + "Node-ID = %d" % self.NodeID)
            self.operationalStateCount = 0
        