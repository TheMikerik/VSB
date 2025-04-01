#!/usr/bin/python

import sys
import cv2
import numpy as np
import math
import struct
from datetime import datetime
import glob
import os

def order_points(pts):
    rect = np.zeros((4, 2), dtype = "float32")
    s = pts.sum(axis = 1)
    rect[0] = pts[np.argmin(s)]
    rect[2] = pts[np.argmax(s)]
    diff = np.diff(pts, axis = 1)
    rect[1] = pts[np.argmin(diff)]
    rect[3] = pts[np.argmax(diff)]
    return rect

def four_point_transform(image, one_c):
    pts = [((float(one_c[0])), float(one_c[1])),
            ((float(one_c[2])), float(one_c[3])),
            ((float(one_c[4])), float(one_c[5])),
            ((float(one_c[6])), float(one_c[7]))]
    
    rect = order_points(np.array(pts))
    (tl, tr, br, bl) = rect
    widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
    widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
    maxWidth = max(int(widthA), int(widthB))
    heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
    heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
    maxHeight = max(int(heightA), int(heightB))
    dst = np.array([
	    [0, 0],
	    [maxWidth - 1, 0],
	    [maxWidth - 1, maxHeight - 1],
	    [0, maxHeight - 1]], dtype = "float32")
    M = cv2.getPerspectiveTransform(rect, dst)
    warped = cv2.warpPerspective(image, M, (maxWidth, maxHeight))
    return warped

def is_occupied(parking_spot_img):
    gray = cv2.cvtColor(parking_spot_img, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    edges = cv2.Canny(blurred, 50, 150)
    edge_count = cv2.countNonZero(edges)
    total_pixels = edges.shape[0] * edges.shape[1]
    edge_percentage = (edge_count / total_pixels) * 100
    return edge_percentage > 4.3, edge_percentage

def load_ground_truth(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    
    ground_truth = []
    for line in lines:
        value = int(line.strip())
        ground_truth.append(value == 1)
    
    return ground_truth

def calculate_accuracy(predictions, ground_truth):
    correct = sum(1 for pred, gt in zip(predictions, ground_truth) if pred == gt)
    total = len(ground_truth)
    return (correct / total) * 100

def main(argv):
    cv2.namedWindow("park_image", 0)

    pkm_file = open('parking_map_python.txt', 'r')
    pkm_lines = pkm_file.readlines()
    pkm_coordinates = []
   
    for line in pkm_lines:
        st_line = line.strip()
        sp_line = list(st_line.split(" "))
        pkm_coordinates.append(sp_line)
    
    test_images = [img for img in glob.glob("test_images_zao/*.jpg")]
    test_images.sort()
    
    all_accuracies = []
    
    for img_path in test_images:
        base_name = os.path.basename(img_path)
        img_name = os.path.splitext(base_name)[0]
        
        gt_path = f"test_images_zao/{img_name}.txt"
        ground_truth = load_ground_truth(gt_path)
        
        park_image = cv2.imread(img_path)
        display_image = park_image.copy()
        
        predictions = []
        
        for i, one_c in enumerate(pkm_coordinates):
            pts = np.array([
                [float(one_c[0]), float(one_c[1])],
                [float(one_c[2]), float(one_c[3])],
                [float(one_c[4]), float(one_c[5])],
                [float(one_c[6]), float(one_c[7])]
            ], dtype=np.int32)
            
            warped_image = four_point_transform(park_image, np.array(one_c))
            one_park_place_image = cv2.resize(warped_image, (80, 80))
            
            occupied, edge_percentage = is_occupied(one_park_place_image)
            predictions.append(occupied)
            
            color = (0, 0, 255) if occupied else (0, 255, 0)
            cv2.polylines(display_image, [pts], True, color, 2)
            
            image_center = pts.mean(axis=0).astype(int)
            cv2.putText(display_image, f"{edge_percentage:.1f}", (image_center[0]-15, image_center[1]), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
        
        accuracy = calculate_accuracy(predictions, ground_truth)
        all_accuracies.append(accuracy)
        print(f"{img_name} - Accuracy: {accuracy:.2f}%")
            
        
        cv2.imshow('park_image', display_image)
        
        key = cv2.waitKey(0)
        if key == 27:
            break
    
    if all_accuracies:
        final_accuracy = sum(all_accuracies) / len(all_accuracies)
        print(f"\nFinal Average Accuracy: {final_accuracy:.2f}%")

if __name__ == "__main__":
    main(sys.argv[1:])