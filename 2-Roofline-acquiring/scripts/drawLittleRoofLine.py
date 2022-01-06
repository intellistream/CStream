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
        
        'core21416000k_rl.csv',
        'core21200000k_rl.csv',
        'core21008000k_rl.csv',
        'core2816000k_rl.csv',
        'core2600000k_rl.csv',
        'core2408000k_rl.csv',
       
    ]
    legend=[
       
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
    groupLine.DrawFigure(xv,yv,legend,"IPM","MINTOPS",0,2000,"Roof_line_of_LittleCore",True)

if __name__ == "__main__":
    main()
    
       
    
