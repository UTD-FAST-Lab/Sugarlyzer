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
  fileBuilds['title'] = 'axTLS'
  fileBuilds['description'] = 'contains information for building axTLS files'
  fileBuilds['remove_errors'] = False
  fileBuilds['no_std_libs'] = True
  fileBuilds['included_files_and_directories'] = [{'included_files' : [], 'included_directories' : []}]
  fileBuilds['build_script'] = '.'
  fileBuilds['source_location'] = '.'
  for l in makeOutput:
    if 'Entering directory' in l:
      currentBuildingDirectory = l.split("'")[1]
      currentBuildingDirectory = os.path.relpath(currentBuildingDirectory,projectDirectory)
    elif l.startswith('cc '):
      fileNameMatch = re.search(r' (\S+\.c)',l)
      if fileNameMatch:
        fileNameText = fileNameMatch.group(1)
        newFileToAdd = {}
        newFileToAdd['file_pattern'] = fileNameText.replace('.','\.') + '$'
        newFileToAdd['included_files'] = re.findall(r'-include ?\S+',l)
        newFileToAdd['included_directories'] = re.findall(r'-I ?\S+',l)
        newFileToAdd['build_location'] = currentBuildingDirectory
        fileBuilds['included_files_and_directories'].append(newFileToAdd)
  makeOutput.close()
  with open('axtlsBuilds.json','w',encoding='utf8') as axtlsBuildsJsonFile:
    json.dump(fileBuilds, axtlsBuildsJsonFile, indent=6)
    

if __name__ == '__main__':
  main()
