import cv2 as cv
import numpy as np


def cv_show(name, img):
    cv.imshow(name, img)
    cv.waitKey(0)
    cv.destroyAllWindows()


def find(img, color='R'):
    # 转化为HSV进行处理
    HSV = cv.cvtColor(img, cv.COLOR_BGR2HSV)

    # 选择需要寻找的颜色，红色R或黄色Y
    lowerColor = np.array([109, 0, 183])
    upperColor = np.array([179, 255, 255])
    if color == 'Y':
        lowerColor = np.array([10, 30, 153])
        upperColor = np.array([30, 250, 255])

    # 指定区域变白，其他变黑
    binary = cv.inRange(HSV, lowerColor, upperColor)

    # 运用中值滤波去除噪声
    median = cv.medianBlur(binary, 9)
    # cv_show('median_%s'%color, median)
    # 得到轮廓
    contours, hierachy = cv.findContours(median, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)

    # 找到原图白色中心点的坐标
    L = len(contours)  # contours轮廓数据是数组，因此用len()测数组长度，为了循环画点使用

    for i in range(L):
        cnt = contours[i]  # cnt表示第i个白色快的轮廓信息
    (x, y), radius = cv.minEnclosingCircle(cnt)  # 得到白色块外接圆的圆心坐标和半径
    center = (int(x), int(y))  # 画center圆心时。x,y必须是整数
    print("%s坐标值:" % color,center)
    # 标出中心点
    circle_color = (0, 0, 255)
    if color == 'Y':
        circle_color = (0, 255, 0)
    cv.circle(img, center, 3, circle_color, 5)  # 传入圆心信息，并画在原图上
    if color == 'Y':
        cv_show('img', img)

    return center
