class actions:
    def __init__(self, command, isRemote, numFiles):
        self.command = command
        self.isRemote = isRemote
        self.numFiles = numFiles
        
class actionSets(actions):
    def __init__(self, numActions):
        self.numActions = numActions
        
class portAndHosts:
    def __init__(self, portAddress, numHosts, hostName):
        self.portAddress = port
        self.numHosts = numHosts
        self.hostName = hostName

def main():
    
    f = open("rakefile", "r")
    text = f.read()
    words = text.splitlines()
    print(words)
    print(words[0])
    print(len(words))
    
    p1 = actions(5561, 5, 'test')
    print(p1)
    print(p1.command)

    #Creating variables for while loop
    arraylength = len(words) - 1
    i = 0
    
    #Processing lines in while loop below
    while (i < arraylength):
        #Removing comment lines
        if (words[i].startswith('#')):
            print("starts with hash")
            words.pop(i)
            arraylength = arraylength - 1
        #Removing empty lines
        elif (words[i] == ''):
            print("is empty line line")
            words.pop(i)
            arraylength = arraylength - 1
        elif (words[i].startswith('\t')):
            print(words[i])
            print("starts with tab")
            i = i+1
        else:
            i = i+1
    
    print(words)
    print(len(words))


    