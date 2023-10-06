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

    #如果没有识别到白色中心点，则之间返回(0, 0)坐标
    if L == 0:
        print("未识别到目标")
        return (0, 0)

    cnt = contours[0]  # cnt表示第i个白色快的轮廓信息
    (x, y), radius = cv.minEnclosingCircle(cnt)  # 得到白色块外接圆的圆心坐标和半径
    center = (int(x), int(y))  # 画center圆心时。x,y必须是整数
    print("%s坐标值:" % color, center)
    # 标出中心点
    line_color = (0, 255, 0)
    # 传入圆心信息，并标在原图上
    cv.line(img, (int(x) - 15, int(y)), (int(x) + 15, int(y)), line_color, 1)
    cv.line(img, (int(x), int(y) + 15), (int(x), int(y) - 15), line_color, 1)
    cv.putText(img, '{}'.format(center), (int(x) - 35, int(y) + 20), cv.FONT_HERSHEY_SIMPLEX, 0.4, line_color)

    #这个判断的只是为了这次任务，还需要进一步改进！！！
    if color == 'Y':
        cv_show('img', img)

    return center
