import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
import matplotlib
matplotlib.use("WebAgg")


cv.namedWindow("zero_img", 0)

# 1
#h, w, c
zero_img = np.zeros(shape=(500, 300, 3), dtype=np.uint8)
print(zero_img.shape)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 2
zero_img[50,50] = (255, 255, 255)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 3
lst = [1, 2, 3, 4, 5, 6, 7, 8]
print(lst[3:])

# 4 cely radek 50
zero_img[50, :] = (0, 0, 255)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 5 rucne
h, w, c = zero_img.shape

for x in range(0, w-1):
    for y in range(0, h-1):
        if y == 50:
            zero_img[y, x] = (0, 255, 0)    

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 6 cely obraz
zero_img[:, :] = (0, 0, 255)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 7 vybrany blok
# zacinam na radku 0 a zajima me informace az na radek 10
zero_img[0:10, :] = (0, 255, 255)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 8 vybrany blok
# zacinam na sloupci 0 a zajima me informace az na sloupec 10
zero_img[:, 0:10] = (0, 255, 255)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 8 vybrany blok
zero_img[0:10, 0:10] = (255, 0, 0)

cv.imshow("zero_img", zero_img)
cv.waitKey(0)

# 9 blok ulozim do samostatneho obrazu
# y1:y2, x1:x2
block = zero_img[0:10, 0:10].copy()
print(block.shape)

cv.imshow("block", block)
cv.imshow("zero_img", zero_img)
cv.waitKey(0)

image_gray = cv.imread("img.png", 1)
image_color = cv.imread("img.png", 1)
img_hconcat = cv.hconcat([image_gray,image_color])
cv.imshow("hconcat", img_hconcat)
cv.waitKey(0)
cv.destroyAllWindows() 

image = cv.imread("img.png", 0)
image_2 = cv.imread("img-2.png", 1)
image_2 = cv.cvtColor(image_2, cv.COLOR_BGR2RGB)

plt.subplot(2, 1, 1)
plt.imshow(image, cmap='gray') #cmap='gray'

plt.subplot(2, 1, 2)
plt.imshow(image_2) 

plt.show()


