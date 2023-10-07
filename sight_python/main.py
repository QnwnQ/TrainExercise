import cv2 as cv
import numpy as np
import color_process as clp

# 打开摄像头
vc = cv.VideoCapture(0)
if vc.isOpened():
    print('success')
else:
    print('failed')

# 命名窗口用于实时显示视频
cv.namedWindow('img')

# 主循环
while 1:
    # flag, img = vc.read()
    img = cv.imread('img9.jpg')
    # 返回两个光点的坐标（x1,y1）（x2,y2）
    (x1, y1), (x2, y2) = clp.find(img, 'R')
    cv.imshow('img', img)

    # 只有按下按键才会打印出坐标以及转动角度，否则就一直循环
    if cv.waitKey(1) != -1:
        rad1 = (x2 - x1) * 64 / 600.
        rad2 = (y1 - y2) * 50 / 480.
        print("水平方向顺时针旋转角度=%f" % rad1)
        print("竖直方向逆时针旋转角度=%f" % rad2)
vc.release()
