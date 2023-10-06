import cv2 as cv
import numpy as np
import color_process as clp
import python_serial as ps
import serial
#打开摄像头
vc = cv.VideoCapture(0)
if vc.isOpened(): print('success')
else : print('failed')

# #打开串口
# ser = serial.Serial('COM3', 9600, timeout=0.5)
# if ser.isOpen() :
#     print("open success")
# else :
#     print("open failed")

#主循环

while 1:
    flag, img = vc.read()
    clp.cv_show('img', img)

    x1, y1 = clp.find(img, 'R')
    x2, y2 = clp.find(img, 'Y')
    # a = input("传输数据a：")
    # b = input("传输数据b：")
    # ps.send(a)
    # ps.send(b)
    # ps.sleep(0.5)  # 起到一个延时的效果
    # data = ps.recv(serial)
    # if data != '':
    #     print("receive : ",data)
    #     if data == b'x':
    #         print("exit")
    #         break
    rad1 = (x2 - x1)*64/600.
    rad2 = (y1 - y2)*50/480.
    print("水平方向顺时针旋转角度=%f" % rad1)
    print("竖直方向顺时针旋转角度=%f" % rad2)
    if cv.waitKey(0) != -1:
        flag, img = vc.read()
vc.release()




