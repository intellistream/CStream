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
def main():
    fileNames=[
        'core51800000k_rl.csv',
        'core51608000k_rl.csv',
        'core51416000k_rl.csv',
        'core51200000k_rl.csv',
        'core51008000k_rl.csv',
        'core5816000k_rl.csv',
        'core5600000k_rl.csv',
        'core5408000k_rl.csv',
        'core21416000k_rl.csv',
        'core21200000k_rl.csv',
        'core21008000k_rl.csv',
        'core2816000k_rl.csv',
        'core2600000k_rl.csv',
        'core2408000k_rl.csv',
    ]
    legend=[
        'B-1.8',
        'B-1.6',
        'B-1.416',
        'B-1.2',
        'B-1.008',
        'B-0.816',
        'B-0.6',
        'B-0.408',
        'L-1.416',
        'L-1.2',
        'L-1.008',
        'L-0.816',
        'L-0.6',
        'L-0.408',
    ]
    xv=[]
    yv=[]
    for i in range(len(fileNames)):
        xt=[]
        yt=[]
        xt,yt=readRoofLineFromCSV(fileNames[i])
        xv.append(xt)
        yv.append(yt)
    groupLine.DrawFigure(xv,yv,legend,"IPM","MINTOPS",0,5000,"Roof_line_of_AMP",True)

if __name__ == "__main__":
    main()
    
       
    
