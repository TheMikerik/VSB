import cv2 # type: ignore
import numpy as np
import mss
from pynput.mouse import Button, Controller
import time

def main():
    template = cv2.imread('t0.png', cv2.IMREAD_COLOR)
    w, h = template.shape[1], template.shape[0]
    mouse = Controller()
    
    retina_display_scale = 2.0
    
    with mss.mss() as sct:
        monitor = sct.monitors[0]
        
        while True:
            
            screenshot = sct.grab(monitor)
            img_rgb = np.array(screenshot)
            img_bgr = cv2.cvtColor(img_rgb, cv2.COLOR_BGRA2BGR)
            
            result = cv2.matchTemplate(img_bgr, template, cv2.TM_CCOEFF_NORMED)
            threshold = 0.8
            
            _, max_val, _, max_loc = cv2.minMaxLoc(result)
            
            if max_val >= threshold:
                center_x = max_loc[0] + w // 2
                center_y = max_loc[1] + h // 2
                mouse.position = (center_x / retina_display_scale, center_y / retina_display_scale)
                time.sleep(0.02)
                mouse.click(Button.left, 1)
                time.sleep(0.1)

if __name__ == "__main__":
    main()