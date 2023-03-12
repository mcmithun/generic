import PyPDF2
import sys
import os 
from sys import argv

# usage
# python3 MergePdf.py /mnt/Desktop/todelete/ /mnt//Desktop/todelete

path = argv[1] # try to get it from user as argument
savepath = argv[2]
merger = PyPDF2.PdfMerger()
for file in os.listdir(path):
    if file.endswith(".pdf"):
        path_with_file = path+'/'+file
        print(path_with_file)
        input = open(path_with_file, 'rb')
        merger.append(input)
    merger.write(f"{savepath}/MergedPdf.pdf")