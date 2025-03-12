import cv2
import matplotlib.pyplot as plt
import os
import math

input_folder = "cv01_images"
output_folder = "cropped"
x1, y1 = 778, 725
w, h = 140, 220
num_spaces = 3
all_crops = []

image_files = [f for f in os.listdir(input_folder) if f.lower().endswith(".jpg")]

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

for img_file in image_files:
    img_path = os.path.join(input_folder, img_file)
    img = cv2.imread(img_path)

    cropped_images = []

    for i in range(num_spaces):
        start_x = x1 + i * w
        cv2.rectangle(img, (start_x, y1), (start_x + w, y1 + h), (0, 255, 0), 2)
        
        crop = img[y1:y1 + h, start_x:start_x + w]
        cropped_images.append(crop)
        all_crops.append(crop)
        
        image_name = os.path.splitext(img_file)[0]
        crop_name = f"{image_name}_crop_{i+1}.jpg"
        cv2.imwrite(os.path.join(output_folder, crop_name), crop)

    plt.figure(figsize=(12, 4))

    plt.subplot(1, num_spaces + 1, 1)
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.axis("off")

    for i, cimg in enumerate(cropped_images, start=1):
        plt.subplot(1, num_spaces + 1, i + 1)
        plt.imshow(cv2.cvtColor(cimg, cv2.COLOR_BGR2RGB))
        plt.title(f"Crop {i}")
        plt.axis("off")

    plt.show()

cols = 3
rows = 4

plt.figure(figsize=(2 * cols, 2 * rows))
for i, crop_img in enumerate(all_crops, start=1):
    plt.subplot(rows, cols, i)
    plt.imshow(cv2.cvtColor(crop_img, cv2.COLOR_BGR2RGB))
    plt.axis("off")

plt.show()
