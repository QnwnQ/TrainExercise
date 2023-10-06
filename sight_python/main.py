import cv2 as cv
import numpy as np
import color_process as clp

#打开摄像头
vc = cv.VideoCapture(0)
if vc.isOpened(): print('success')
else : print('failed')

#主循环

while 1:
    flag, img = vc.read()
    clp.cv_show('img', img)

    x1, y1 = clp.find(img, 'R')
    x2, y2 = clp.find(img, 'Y')
    rad1 = (x2 - x1)*64/600.
    rad2 = (y1 - y2)*50/480.
    print("水平方向顺时针旋转角度=%f" % rad1)
    print("竖直方向逆时针旋转角度=%f" % rad2)
    if cv.waitKey(0) != -1:
        flag, img = vc.read()
vc.release()




