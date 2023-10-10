import cv2
import numpy as np
import os


def gamma_trans(img, gamma):  # gamma函数处理
    gamma_table = [np.power(x / 255.0, gamma) * 255.0 for x in range(256)]  # 建立映射表
    gamma_table = np.round(np.array(gamma_table)).astype(np.uint8)  # 颜色值为整数
    return cv2.LUT(img, gamma_table)  # 图片颜色查表。另外可以根据光强（颜色）均匀化原则设计自适应算法。


def nothing(x):
    pass


def baoguang(image):

    value_of_gamma = 1000
    value_of_gamma = value_of_gamma * 0.01  # 压缩gamma范围，以进行精细调整
    image_gamma_correct = gamma_trans(image, value_of_gamma)  # 2.5为gamma函数的指数值，大于1曝光度下降，大于0小于1曝光度增强
    return image_gamma_correct