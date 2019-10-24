# -*- coding: utf-8 -*-
"""
Created on Thu Aug 22 15:46:00 2019

@author: Han
"""

import json, sys
import unicodecsv as csv
#if you are not using utf-8 files, remove the next line

#check if you pass the input file and output file
if sys.argv[1] is not None and sys.argv[2] is not None:
    fileInput = sys.argv[1]
    fileOutput = sys.argv[2]
    inputFile = open(fileInput, 'r') #open json file
    outputFile = open(fileOutput, 'wb') #load csv file
    output = csv.writer(outputFile)
    header = 0
    for line in inputFile:
        
        if len(line) < 5:
            continue
        data = json.loads(line)
        
        outputkeys = list(data.keys()) + [ "user_"+ s for s in data["user"].keys()]
    
        if header == 0:
            
            output.writerow(outputkeys)
            header = 1
        outputvalues = list(data.values()) + list(data["user"].values())
        output.writerow(outputvalues)
    
    
   