import json
import csv
import sys


def get_nested_values(value, key='', path=''):
    """Get the innermost values from a json as a dictionary
    
    Traverses json fields as if they were a tree. Features
    have the form <feature>.<nested feature>
    """

    if isinstance(value, dict):
        path += key
        if key != '': path += '.'
        leaves = {}
        for i in value.keys():
            leaves.update(get_nested_values(value[i], i, path))
        return leaves
    elif isinstance(value, list):
        path += key + '.'
        if len(value) > 0 and isinstance(value[0], dict):
            leaves = {}
            for i in value:
                leaves.update(get_nested_values(i, key, path))
        else:
            leaves = {path:str(value).strip('[]')}
        return leaves
    else:
        path += key
        return {path : value}

def json2csv(list_, out, sep=','):
    """ Converts list of jsons into a csv file

    Parameters
    ----------
    list_: list<dict>
           List of dictionaries (jsons) to write into CSV
    out: <str>
         Name of CSV file
    sep: <str>, optional
         CSV delimiter
    """
    header = set()
    data = []
    for json_ in list_:
        data.append(get_nested_values(json_))
        header.update(data[-1].keys())
    with open(out, 'w', encoding='utf8') as f:
        writer = csv.DictWriter(f, fieldnames=sorted(header), delimiter=sep)
        writer.writeheader()
        writer.writerows(data)
		
		
		
if sys.argv[1] is not None and sys.argv[2] is not None:
    fileInput = sys.argv[1]
    fileOutput = sys.argv[2]
    inputFile = open(fileInput, 'r') #open json file
    
    header = 0
    jsons = []
    for line in inputFile:
        
        if len(line) < 5:
            continue
        
       
        data = json.loads(line)
        jsons.append(data)
    json2csv(jsons, fileOutput)