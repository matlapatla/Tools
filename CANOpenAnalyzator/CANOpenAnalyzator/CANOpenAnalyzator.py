
import sys
import string

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
        if (self.cs == "1"):
            print (self.TimeOffset + "!!! start " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "2"):
            print (self.TimeOffset + "!!! stop " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "80"): #128 
            print (self.TimeOffset + "!!! enter pre-operational " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "81"): #129
            print (self.TimeOffset + "!!! reset node " + "Node-ID %d" % int(self.NodeID,16))
        elif (self.cs == "82"): #130
            print (self.TimeOffset + "!!! reset communication " + "Node-ID %d" % int(self.NodeID,16))


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

    def DisplayDecoded(self):
        if (self.s == "00"):
            print (self.TimeOffset + "--- Boot-up " + "Node-ID %d" % self.NodeID)
        elif (self.s == "04"):
            print (self.TimeOffset + "--- Stopped " + "Node-ID %d" % self.NodeID)
        elif (self.s == "05"): 
            print (self.TimeOffset + " Operational " + "Node-ID %d" % self.NodeID)
        elif (self.s == "7F"): #127
            print (self.TimeOffset + "--- Pre-operational " + "Node-ID %d" % self.NodeID)
        



if __name__ == '__main__':
    if (len(sys.argv) == 1):
        print ("Start the script with the name of the log file stated as the parameter.")
    else:
       with open(sys.argv[1],'r',encoding="utf8") as inpFile:
           for line in inpFile:
               rawwords = line.split(' ')
               words = []
               for tempword in rawwords:
                   if len(tempword) > 0:
                       words.append(tempword)
               if len(words) > 3:
                   if (words[3] == "0000"):
                       NMTStartStopServiceInstance = NMTStartStopService(words[3], words[6], words[7], words[1])
                       NMTStartStopServiceInstance.DisplayDecoded()
                   if (words[3] >= "0700" and words[3] < "0800"):
                       NMTErrorControlInstance = NMTErrorControl(words[3], 0, words[6],  words[1])
                       NMTErrorControlInstance.DisplayDecoded()
        



        
        



