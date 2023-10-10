import cv2 as cv
import numpy as np
import color_process as clp
import serial
import python_serial as pyser

# 打开摄像头
vc = cv.VideoCapture(0)
if vc.isOpened():
    print('success')
else:
    print('failed')

# 打开串口
ser = pyser.open_ser()

# 命名窗口用于实时显示视频
cv.namedWindow('img')

# 创建储存10次坐标的列表
X_1 = [0 for i in range(1, 10 + 1)]
Y_1 = [0 for i in range(1, 10 + 1)]
X_2 = [0 for i in range(1, 10 + 1)]
Y_2 = [0 for i in range(1, 10 + 1)]

i = 0
j = 0
# 主循环
while 1:

    # 跳过第一次图像识别
    if j == 0:
        j = j+1
        continue

    flag, img = vc.read()

    # 返回两个光点的坐标（x1,y1）（x2,y2）
    (x1, y1), (x2, y2) = clp.find(img)
    cv.imshow('img', img)
    if (x1,y1) != (0, 0):
        X_1[i], Y_1[i] = x1, y1
        X_2[i], Y_2[i] = x2, y2

    if i == 9:
        i = 0
    else:
        i = i + 1

    # 只有按下按键才会打印出坐标以及转动角度，否则就一直循环
    if cv.waitKey(1) != -1:
        # 取平均后的值
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
        rad2 = (y1_ave - y2_ave) * 50 / 480.
        print("水平方向顺时针旋转角度=%f" % rad1)
        print("竖直方向逆时针旋转角度=%f" % rad2)

        # 将数据转化为字符串
        if rad1 >= 0:
            rad1_serial = '+' + str(rad1)
        else:
            rad1_serial = '-' + str(abs(rad1))
        if rad2 >= 0:
            rad2_serial = '+' + str(rad2)
        else:
            rad2_serial = '-' + str(abs(rad2))
        # 发送字符串，开动电机
        pyser.send_msg(ser, rad1_serial + ',' + rad2_serial)  # 写数据
        pyser.read_msg(ser)

serial.close_ser()
vc.release()
