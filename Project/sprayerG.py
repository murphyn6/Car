#termios.error: (5, 'Input/output error')

import numpy as np
from matplotlib import pyplot as plt
import serial
import math
import time
import cv2
import time


# taking the input from webcam 
vid = cv2.VideoCapture(0) #1/2
if not vid.isOpened():
	print("camera fail")
	
ser = serial.Serial('/dev/ttyACM0', 9600) #,timeout=1
ser.flush()
#time.sleep(2)
#ser1 = serial.Serial('/dev/ttyACM1', 9600, timeout=0.1)
#vid = 2341  # Put your VID here
#pid = 0o0053  # Put your PID here
#port_url = f"hwgrep://{vid}:{pid}"
#ser = serial.serial_for_url(url=port_url)
ex = 0
tp = 300
ty = 315
#sendy = 0
#sendp = 0
off = 'off'
  

def detect_green(image):
    #time.sleep(.25);
# Function to detect red color in the image
# Convert image to HSV color space
    #time.sleep(1)
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    
    # Define lower and upper bounds for green color detection in HSV
    lower_green = np.array([40, 30, 100]) #40s
    upper_green = np.array([80, 255, 255]) #70
    
    # Create a mask for the green color
    mask = cv2.inRange(hsv, lower_green, upper_green)
    
    # Apply morphological operations to remove noise
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
    
    # Find contours in the mask
    contours,_= cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    min_area = 4000
    
    #initalize counters
    prev_ty, prev_tp = 0, 0
    
    # Draw bounding boxes around detected green objects
    for contour in contours:
        area = cv2.contourArea(contour)
       
        #filter
        if area > min_area :

            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
            #time.sleep(.25)
            ty = x + math.floor(w / 2)
            tp = y + math.floor((7 * h) / 20)
            if ty!= prev_ty or tp != prev_tp:
                # Converting coordinates to pitch and yaw angles for servos
                sendy = str(abs(math.floor(ty * (-45 / 573) + 117.9)))#abs
                sendp = str(abs(math.floor(tp * (-45 / 470) + 75)))#abs
                send = 'X{0}Y{1}'.format((sendy), (sendp))
                # Sending the coordinates to servos
                #time.sleep(1)
                ser.write(send.encode('utf-8'))
                #ser.flush()
                time.sleep(0.01)
                print(send)
                prev_ty, prev_t = ty, tp
                #if contours != ():
                    #time.sleep(1)
                    #ser.write(send.encode('utf-8'))
                    #ser.close()
                    #ser1.write(send.encode('utf-8'))
                    #time.sleep(0.01) #.001
                    #print(send)
                
                    #Update counters
                    #prev_ty, prev_t = ty, tp

    return image
while True: 
  
  
    # capturing the current frame 
    _, frame = vid.read() #ret
    
    frame = cv2.flip(frame,1)
  
    # displaying the current frame 
    #cv2.imshow('frame', frame)  
    #time.sleep(1)
    #if not frame.read(frame):
		#break

    
    green_detected_frame = detect_green(frame)
    
   # rgb_image = cv2.cvtColor(green_detected_frame, cv2.COLOR_BGR2RGB)
    #plt.imshow(rgb_image)
    #plt.axis('off')
    #plt.show()
    
    # Display the frame with bounding boxes
    cv2.imshow('Green Object Detection', green_detected_frame)
    
    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


vid.release()
cv2.destroyAllWindows()
