from ntpath import join
from re import split
class PDO:
    """Common class for the T_PDO"""
    PDOCount = 0
    def __init__ (self, CANID, timeOffset, UserDataLength, Words, lifeCyclePosition1, lifeCyclePosition2 = 0):

        self.CANID = CANID
        self.timeOffset = timeOffset
        self.UserDataLength = UserDataLength
        self.Words = Words
        self.counterNow = 0
        self.counterBefore = 0
        self.counterDifference = 0
        self.timeOffsetBefore = timeOffset
        self.timeOffsetDifferenceRounded = 0
        self.lifeCyclePosition1 = lifeCyclePosition1
        self.lifeCyclePosition2 = lifeCyclePosition2
        PDO.PDOCount += 1

    def DisplayDecoded(self, CANID, TimeOffset, UserDataLength, Words, difference):

        self.CANID = CANID
        self.timeOffset = TimeOffset
        self.UserDataLength = UserDataLength
        self.Words = Words
        lenght = 0
        timeOffsetRounded = []
        timeOffsetBeforeRounded = []
        counterNowJoined = ""

        lenght = len(self.Words)
        if (lenght >= 14):
            if (self.lifeCyclePosition2 != 0):
                seq = (self.Words[self.lifeCyclePosition2], self.Words[self.lifeCyclePosition1])
                counterNowJoined = "".join(seq)
            else:
                counterNowJoined = self.Words[self.lifeCyclePosition1]
            self.counterNow = int(counterNowJoined,16)
            self.counterDifference = self.counterNow - self.counterBefore
            self.counterBefore = self.counterNow            

        print(self.timeOffset + " CAN-ID=%x " % int(self.CANID,16) + " UserDataLength=%d " % int(self.UserDataLength) + " " +  " ".join(self.Words[6:]) + " LifeSignalCounterDifference = %d" % self.counterDifference)        
        
        if (self.counterDifference != 0):
            timeOffsetRounded = self.timeOffset.split(".")
            timeOffsetBeforeRounded = self.timeOffsetBefore.split(".")
            self.timeOffsetDifferenceRounded = int(timeOffsetRounded[0]) - int(timeOffsetBeforeRounded[0])
            self.timeOffsetBefore = self.timeOffset                        
            #print(self.timeOffset + " CAN-ID=%x " % int(self.CANID,16) + " UserDataLength=%d " % int(self.UserDataLength) + " " +  " ".join(self.Words[6:]) + " LifeSignalCounterDifference = %d" % self.counterDifference)        
            
            if (self.timeOffsetDifferenceRounded > difference):
               #print(self.timeOffset + " CAN-ID=%x " % int(self.CANID,16) + " UserDataLength=%d " % int(self.UserDataLength) + " " +  " ".join(self.Words[6:]) + " LifeSignalCounterDifference = %d" % self.counterDifference)        
               #print (" timeOffsetDifferenceRounded = %d" % self.timeOffsetDifferenceRounded ) 
               print (" !!!!!!!!!!!!!!!!!!! timeOffsetDifferenceRounded %d" % self.timeOffsetDifferenceRounded )
            else:
                print (" timeOffsetDifferenceRounded = %d" % self.timeOffsetDifferenceRounded )