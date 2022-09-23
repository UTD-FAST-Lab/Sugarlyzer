import os
import sys
import re
import json

def main():
  os.system('make linuxconf > makeOut.txt 2>&1')
  projectDirectory = os.getcwd()
  makeOutput = open('makeOut.txt', 'r')
  currentBuildingDirectory = ''
  fileBuilds = {}
  for l in makeOutput:
    if 'Entering directory' in l:
      currentBuildingDirectory = l.split("'")[1]
      currentBuildingDirectory = os.path.relpath(currentBuildingDirectory,projectDirectory)
    elif l.startswith('cc '):
      fileNameMatch = re.search(r' (\S+\.c)',l)
      if fileNameMatch:
        fileNameText = fileNameMatch.group(1)
        fileBuilds[fileNameText] = {}
        fileBuilds[fileNameText]['buildLocation'] = currentBuildingDirectory
        fileBuilds[fileNameText]['includedDirectories'] = re.findall(r'-I ?\S+',l)
        fileBuilds[fileNameText]['includedFiles'] = re.findall(r'-include ?\S+',l)
  makeOutput.close()
  with open('axtlsBuilds.json','w',encoding='utf8') as axtlsBuildsJsonFile:
    json.dump(fileBuilds, axtlsBuildsJsonFile, indent=6)
    

if __name__ == '__main__':
  main()
