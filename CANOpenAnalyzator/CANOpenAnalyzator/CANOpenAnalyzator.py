
import sys
import string
import NMTStartStopService
import NMTErrorControl
import SYNCObject
import EMCYObject
import PDO

if __name__ == '__main__':
    T_PDO1_018DObjectInstance = 0
    T_RDO1_0200ObjectInstance = 0
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
                       NMTStartStopServiceInstance = NMTStartStopService.NMTStartStopService(words[3], words[6], words[7], words[1])
                       NMTStartStopServiceInstance.DisplayDecoded()
                   if (words[3] >= "0700" and words[3] < "0800"):
                       NMTErrorControlInstance = NMTErrorControl.NMTErrorControl(words[3], 0, words[6],  words[1])
                       NMTErrorControlInstance.DisplayDecoded()
                   if ((words[3] == "0080") and len(words) > 4):
                       SYNCObjectInstance = SYNCObject.SYNCObject(words[3], words[1], words[6])
                       SYNCObjectInstance.DisplayDecoded()
                   if ((words[3] == "0080") and len(words) > 4):
                       SYNCObjectInstance = SYNCObject.SYNCObject(words[3], words[1])
                       SYNCObjectInstance.DisplayDecoded()
                   if (words[3] >= "0080" and words[3] < "0180"):
                       EMCYObjectInstance = EMCYObject.EMCYObject(words[3], words[1])
                       EMCYObjectInstance.DisplayDecoded()
                   if (words[3] == "018D"):
                       if (isinstance(T_PDO1_018DObjectInstance, PDO.PDO)):
                           T_PDO1_018DObjectInstance.DisplayDecoded(words[3], words[1], words[5], words, 3000)
                       else:
                           pass
                           #T_PDO1_018DObjectInstance = PDO.PDO(words[3], words[1], words[5], words, 13)
                   if (words[3] == "020E"):
                       if (isinstance(T_RDO1_0200ObjectInstance, PDO.PDO)):
                           T_RDO1_0200ObjectInstance.DisplayDecoded(words[3], words[1], words[5], words, 400)
                       else:                      
                           T_RDO1_0200ObjectInstance = PDO.PDO(words[3], words[1], words[5], words, 10, 11)
                      
