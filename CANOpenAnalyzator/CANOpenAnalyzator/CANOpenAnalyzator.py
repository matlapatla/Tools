
import sys
import string

class NMTStartStopService:
    'Common class for the CANOpen NMT Start/Stop service'
    NMTStartStopServiceCount = 0
    def __init__ (self, CANID, cs, NodeID):
        self.CANID = CANID
        self.cs = cs
        self.NodeID = NodeID
        NMTStartStopService.NMTStartStopServiceCount += 1

    def DisplayDecoded(self):
        if (cs == 1):
            print ("start " + "Node-ID"  + NodeID)
        elif (cs == 2):
            print ("stop " + "Node-ID"  + NodeID)
        elif (cs == 128):
            print ("enter pre-operational " + "Node-ID"  + NodeID)
        elif (cs == 129):
            print ("reset node " + "Node-ID"  + NodeID)
        elif (cs == 130):
            print ("reset communication " + "Node-ID"  + NodeID)


if __name__ == '__main__':
    if (len(sys.argv) == 1):
        print ("Start the script with the name of the log file stated as the parameter.")
    else:
       with open(argv[1],'r',encoding="utf8") as inpFile:
           for line in inpFile:
               words = line.split(' ')
               if (words[3] == "0000"):
                   NMTStartStopServiceInstance = NMTStartStopService(0, words[6], words[7])
                   NMTStartStopServiceInstance.DisplayDecoded()

        



        
        



