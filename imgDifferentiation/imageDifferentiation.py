import cv2
import numpy as np
import matplotlib.pyplot as plt

image = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)

sobel_x = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)  # 
sobel_y = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)  

# 微分結果の絶対値を計算
sobel_x = np.abs(sobel_x)
sobel_y = np.abs(sobel_y)

# 画像の色を反転 (255 - ピクセル値)
sobel_x_inverted = 255 - sobel_x
sobel_y_inverted = 255 - sobel_y

_, sobel_x_binary = cv2.threshold(sobel_x_inverted, 128, 255, cv2.THRESH_BINARY)
_, sobel_y_binary = cv2.threshold(sobel_y_inverted, 128, 255, cv2.THRESH_BINARY)

plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(sobel_x_binary, cmap='gray')
plt.title('Sobel X (Binary)')

plt.subplot(1, 2, 2)
plt.imshow(sobel_y_binary, cmap='gray')
plt.title('Sobel Y (Binary)')

plt.show()
