#!/usr/bin/env python3
import groupLine as groupLine
import csv
def readRoofLineFromCSV(a):
    print('load'+a)
    with open(a, 'r') as f:
        reader = csv.reader(f)
        #reader = [each for each in csv.DictReader(f, delimiter=',')]
        result = list(reader)
        rows=len(result)
        print('rows=',rows)
        firstRow = result[0]
        print(firstRow)
        index=0
        #define what may attract our interest
        idxMflops=0
        idxIPM=0
       
        for i in firstRow:
            #print(i)
            if(i=='mfops'):
               idxMflops=index
            if(i=='IPM'):
               idxIPM=index
            index=index+1
        #read the valid stages
        vdataEntries=0
        mflopsList=[]
        ipmList=[]
       
        for k in range(1,rows):
            #print(result[k][idxMflops])
          
            if(result[k][1]!='NA'):
                vdataEntries+=1
                mflopsList.append(int(result[k][idxMflops]))
                ipmList.append(int(result[k][idxIPM]))
        return ipmList, mflopsList

def genSpeedUp(a,b):
    speedx=[]
    for i in range(len(a)):
        k=float(b[i])/float(a[i])
        speedx.append(k)
    return speedx

def main():
    fileNames=[
        'core51800000k_rl.csv', #0
        'core51608000k_rl.csv', #1
        'core51416000k_rl.csv', #2
        'core51200000k_rl.csv', #3
        'core51008000k_rl.csv', #4
        'core5816000k_rl.csv',  #5
        'core5600000k_rl.csv', #6
        'core5408000k_rl.csv',  #7
        'core21416000k_rl.csv', #8
        'core21200000k_rl.csv', #9
        'core21008000k_rl.csv', #10
        'core2816000k_rl.csv',  #11
        'core2600000k_rl.csv', #12
        'core2408000k_rl.csv', #13
    ]
    legend=[
        
        'f=1.416',
        'f=1.2',
        'f=1.008',
        'f=0.816',
        'f=0.6',
        'f=0.408',
        '1.8VS1.416',
        '1.6VS1.416'
      
    ]
    xv=[]
    yv=[]
    xv2=[]
    yv2=[]
    for i in range(len(fileNames)):
        xt=[]
        yt=[]
        xt,yt=readRoofLineFromCSV(fileNames[i])
        xv.append(xt)
        yv.append(yt)
    for i in  range(len(legend)-2):
        tt=genSpeedUp(yv[8+i],yv[2+i])
        xv2.append(xv[2+i])
        yv2.append(tt)
    xv2.append(xv[0])
    yv2.append(genSpeedUp(yv[8],yv[0]))
    xv2.append(xv[1])
    yv2.append(genSpeedUp(yv[8],yv[1]))
    groupLine.DrawFigureYnormal(xv2,yv2,legend,"IPM","MINTOPSpeedUp",0,3,"speed_up",True)
if __name__ == "__main__":
    main()
    
       
    
