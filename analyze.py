import simplejson
import os
from argparse import ArgumentParser
from datetime import timedelta

parser = ArgumentParser()

parser.add_argument('--outputDir', required=True, help='The dir which contains build analyzer output')
parser.add_argument('--maxLength', type=int, required=True, help='The max elements count for each analysis to output')
args = parser.parse_args()

outputDir = args.outputDir
maxLength = args.maxLength

jsonFiles = [jsFile for jsFile in os.listdir(outputDir) if jsFile.endswith('.json')]

def printElement(element):
    durationUs = int(element['duration'])
    count = int(element['count'])
    duration = timedelta(microseconds = durationUs)
    average = timedelta(microseconds = durationUs / count)
    print('Total time: ' + str(duration), end = ' ')
    print('Average time: ' + str(average), end = ' ')
    print('Count: ' + element['count'], end = ' ')
    if 'value' in element:
        print(element['value'])

for jsFile in jsonFiles:
    with open(outputDir + '/' + jsFile, 'r') as fp:
        js = simplejson.load(fp)
        print(js['eventType'] + ':\n')
        
        statistics = js['statistics']
        
        for element in statistics[:maxLength]:
            printElement(element)
        
        print('\n')
