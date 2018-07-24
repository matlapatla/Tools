class SYNCObject:
    'Common class for the CANOpen SyncObject service'
    SYNCObjectCount = 0
    def __init__ (self, CANID, TimeOffset, Counter = "-1"):
        self.CANID = CANID
        self.Counter = Counter
        self.TimeOffset = TimeOffset
        SYNCObject.NMTStartStopServiceCount += 1

    def DisplayDecoded(self):
        if (self.Counter == "-1"):
            print (self.TimeOffset + "!!- SYNC-Object ")
        else:
            print (self.TimeOffset + "!!- SYNC-Object " + " Counter = %d" % int(self.Counter,16))

