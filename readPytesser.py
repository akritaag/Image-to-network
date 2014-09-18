import os
from PIL import Image
from pytesseract.pytesseract import *

def run_tess():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    #tesseract_exe_name = '/usr/local/bin/tesseract'
    tesseract_exe_name = 'tesseract'
    output_filename = script_dir

    #/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork
    length = 22
    for i in range(1,length+1):
        filename = str(i)+'.jpg'
        #print filename
        input_path = os.path.join(script_dir,'images',filename)
        #print input_path
        filename = 'Img'+str(i)
        #print filename
        output_path = os.path.join(script_dir,'images','out', filename)
        #print output_path
        try:
            im = Image.open(input_path)
            im.load()
            im.split()
            #text = image_to_string(im)
            if os.path.isfile(output_path+'.txt'):
                print filename+'.txt exists.'
            else:
                status = run_tesseract(input_path,output_path)
        except:
            pass


if __name__ == '__main__':
    run_tess()