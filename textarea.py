import cv2
import readPytesser
import os


def cleanup(filename):
    ''' tries to remove the given filename. Ignores non-existent files '''
    try:
        os.remove(filename)
    except OSError:
        pass

#get file
script_dir = os.path.dirname(os.path.abspath(__file__))
file_name = '12'
input_path = os.path.join(script_dir,'images',file_name)

image = cv2.imread(input_path+'.jpg')
gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY) # grayscale
_,thresh = cv2.threshold(gray,150,150,cv2.THRESH_BINARY_INV) # threshold
kernel = cv2.getStructuringElement(cv2.MORPH_CROSS,(3,3))
dilated = cv2.dilate(thresh,kernel,iterations = 13) # dilate
contours, hierarchy = cv2.findContours(dilated,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE) # get contours

# for each contour found, draw a rectangle around it on original image
contour_no = 1
try :
    for contour in contours:
        # get rectangle bounding contour
        [x,y,w,h] = cv2.boundingRect(contour)
        
        # discard areas that are too large
        if h>300 and w>300:
        #if h>100 and w>100:
            continue
        
        # discard areas that are too small
        #if h<40 or w<40:
        if h<51 or w<51:
            continue
        
        # draw rectangle around contour on original image
        img = cv2.rectangle(image,(x,y),(x+w,y+h),(255,0,255),2)
        roi = gray[y:y+h, x:x+w]
        input_filename = str(file_name) + '_' + str(contour_no)
        filename = input_filename+'.jpg'
        cv2.imwrite(filename,roi)
        readPytesser.run_tess(filename,script_dir,contour_no,roi)
        contour_no += 1
except:
    pass
'''
finally:
    cleanup(filename)
'''

# write original image with added contours to disk
#cv2.imwrite("contoured.jpg", image)
cv2.imshow("image",image)
ch = cv2.waitKey(0)