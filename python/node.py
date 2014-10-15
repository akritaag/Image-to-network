import sys,csv,os,re

class node:
    '''
    first = last = None
    
    def __init__(self, fnode):
        self.add(fnode)
    
    def add(self, newNode):
        if self.first is None:
            self.first = self.last = newNode
        else:
            self.last.nextEl = self.last = newNode
    '''
    
    x = [0,0]
    y = [10,10]
    text = 'default'
    
    def __init__(self,x=[0,0],y=[10,10],text = 'default'):
        self.x = x
        self.y = y
        self.text = text

    def isvalid(self):
         return self.text != null

    def getnode(self):
        return self
    
class graph:
    #check for file
    def isgraph(self,filename):
        return os.path.isfile(str(filename)+'.csv')
    
    #create the graph from all the coordinates and text.
    def __init__(self,filename,output_path,numNodes,x,y):
        allNode = []
        if self.isgraph(filename) == False:
            for i in range(1,numNodes):
                output_filename = 'out'+ str(filename) +'_' + str(i) + '.txt'
                output_filepath = os.path.join(output_path,'out',output_filename)
                #print output_path
                with open (str(output_filepath), "r") as myfile:
                    try:
                        #print 'try'
                        #print os.stat(str(output_filepath))[6]
                        if (os.stat(str(output_filepath))[6]==0):
                        #print 'empty!'
                            continue
                                #elif:
                                #print 'spell check'
                        else:
                            #print i
                            data=myfile.read().replace('\n', ' ')
                            data = data.lower()
                            flag = 0
                            for d in data:
                                if d != ' ':
                                    flag = 1
                            if flag == 1:
                                data = re.sub(r'[^\w|\&]',' ', data)
                                print data
                                n = node(x[i],y[i],data)
                                a = n.getnode()
                                print a
                                allNode += [a]
                    except:
                        pass
            self.printgraph(allNode,filename,output_path)
        else:
            print 'graph already exists.'
    

    #fetch the file
    def getgraph(self,filename):
        if(self.isgraph(filename)):
            print 'get graph under construction.'
    #read csv

    def printgraph(self,allNode,filename,output_path):
        if self.isgraph(filename) == False:
            #writer = csv.writer(open(str(filename)+'.csv','w'))
            print len(allnode)
            for n in allNode:
                #print n.x[0]
                a = [n.x[0],n.x[1],n.y[0],n.y[1],n.text]
                print a
    #writer.writerow(a)
        else:
            print 'graph already exists.'
