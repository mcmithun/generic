from PIL import Image, ImageEnhance, ImageFilter
import os, sys

path = './images' # try to get it from user as argument
pathOut = '/editedimages' #try to get it too from usrer


for filename in os.listdir(path):
    img = Image.open(f"{path}/{filename}")
    edit = img.filter(ImageFilter.SHARPEN).convert('L')
    file_name = os.path.splitext(filename)[0]
    edit.save(f'.{pathOut}/{file_name}_thump.JPEG')
    
