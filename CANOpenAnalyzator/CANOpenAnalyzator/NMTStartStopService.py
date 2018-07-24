
class NMTStartStopService:
    'Common class for the CANOpen NMT Start/Stop service'
    NMTStartStopServiceCount = 0
    def __init__ (self, CANID, cs, NodeID, TimeOffset):
        self.CANID = CANID
        self.cs = cs
        self.NodeID = NodeID
        self.TimeOffset = TimeOffset
        NMTStartStopService.NMTStartStopServiceCount += 1

    def DisplayDecoded(self):
        if (self.cs == "01"):
            print (self.TimeOffset + "!!! start " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "02"):
            print (self.TimeOffset + "!!! stop " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "80"): #128 
            print (self.TimeOffset + "!!! enter pre-operational " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "81"): #129
            print (self.TimeOffset + "!!! reset node " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "82"): #130
            print (self.TimeOffset + "!!! reset communication " + "Node-ID %d" % int(self.NodeID,16))


