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

#创建储存10次坐标的列表
X_1 = [0 for i in range(1, 10 + 1)]
Y_1 = [0 for i in range(1, 10 + 1)]
X_2 = [0 for i in range(1, 10 + 1)]
Y_2 = [0 for i in range(1, 10 + 1)]

i = 0
# 主循环
while 1:
    flag, img = vc.read()
    # 返回两个光点的坐标（x1,y1）（x2,y2）
    (x1, y1), (x2, y2) = clp.find(img, 'R')
    cv.imshow('img', img)

    X_1[i], Y_1[i] = x1, y1
    X_2[i], Y_2[i] = x2, y2
    # 只有按下按键才会打印出坐标以及转动角度，否则就一直循环
    if cv.waitKey(1) != -1:
        #取平均后的值
        x1_ave, y1_ave = 0, 0
        x2_ave, y2_ave = 0, 0

        for i in range(10):
            x1_ave = x1_ave + X_1[i]
            y1_ave = y1_ave + Y_1[i]
            x2_ave = x2_ave + X_2[i]
            y2_ave = y2_ave + Y_2[i]

        x1_ave = x1_ave / 10
        y1_ave = y1_ave / 10
        x2_ave = x2_ave / 10
        y2_ave = y2_ave / 10
        rad1 = (x2_ave - x1_ave) * 64 / 600.
        rad2 = (y2_ave - y1_ave) * 50 / 480.
        print("水平方向顺时针旋转角度=%f" % rad1)
        print("竖直方向顺时针旋转角度=%f" % rad2)

    if i == 9:
        i = 0
    else:
        i = i + 1
vc.release()
