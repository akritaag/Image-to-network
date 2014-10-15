import os
from PIL import Image
from pytesseract.pytesseract import *

def run_tess(input_file,output_path,node_no,image_chunk):
    #tesseract_exe_name = '/usr/local/bin/tesseract'
    tesseract_exe_name = 'tesseract'
    output_filename = 'out' + str(input_file)
   

    try:
        input_path = os.path.join(output_path,input_file+'.jpg')
        output_path = os.path.join(output_path,'out',output_filename)
    
        im = Image.open(input_path)
        im.load()
        im.split()
    
        if os.path.isfile(output_path+'.txt'):
            print filename+'.txt exists.'
        else:
            status = run_tesseract(input_path,output_path)
    except:
        pass


if __name__ == '__main__':
    run_tess()