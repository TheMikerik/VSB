import cv2 as cv
import numpy as np
import os
import matplotlib.pyplot as plt
from pathlib import Path

os.makedirs("out-red", exist_ok=True)
os.makedirs("out-green", exist_ok=True)

image_files = [f for f in os.listdir("test-images") if f.endswith(".png")]
correct = 0
total = len(image_files)

for image_name in image_files:
    image_path = os.path.join("test-images", image_name)
    image = cv.imread(image_path)
    image = cv.resize(image, (300, 600))
    
    hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)
    
    red_mask = cv.bitwise_or(
        cv.inRange(hsv, np.array([0, 100, 100]), np.array([10, 255, 255])),
        cv.inRange(hsv, np.array([160, 100, 100]), np.array([180, 255, 255]))
    )
    
    green_mask = cv.inRange(hsv, np.array([40, 50, 50]), np.array([90, 255, 255]))
    
    red_pixels = cv.countNonZero(red_mask)
    green_pixels = cv.countNonZero(green_mask)
    
    color = None
    if red_pixels > green_pixels and red_pixels > 100:
        color = "red"
    elif green_pixels > red_pixels and green_pixels > 100:
        color = "green"
    
    if color:
        fig, ax = plt.subplots(1, 3, figsize=(15, 5))
        
        ax[0].imshow(cv.cvtColor(image, cv.COLOR_BGR2RGB))
        ax[0].set_title("Original Image")
        ax[0].axis("off")
        
        ax[1].imshow(red_mask, cmap="gray")
        ax[1].set_title(f"Red Region\nPixels: {red_pixels}")
        ax[1].axis("off")
        
        ax[2].imshow(green_mask, cmap="gray")
        ax[2].set_title(f"Green Region\nPixels: {green_pixels}")
        ax[2].axis("off")
        
        plt.tight_layout()
        plt.savefig(os.path.join(f"out-{color}", f"{Path(image_name).stem}_result.png"))
        plt.close()
        
        print(f"Detected {color} light in {image_name}")
        
        if (color == "red" and "red" in image_name.lower()) or (color == "green" and "green" in image_name.lower()):
            correct += 1

if total > 0:
    print(f"Accuracy: {(correct/total)*100:.2f}% ({correct}/{total})")