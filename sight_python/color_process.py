import cv2 as cv
import numpy as np
import baoguang as bg


# 显示并暂停的函数
def cv_show(name, img):
    cv.imshow(name, img)
    cv.waitKey(0)
    cv.destroyAllWindows()


# 图像处理返回色块的轮廓信息的函数
def process(img):
    # 以下是对黄色激光点的处理

    # 转化为HSV进行处理
    HSV = cv.cvtColor(img, cv.COLOR_BGR2HSV)

    lowerColor = np.array([10, 0, 235])
    upperColor = np.array([156, 255, 255])

    # 指定区域变白，其他变黑
    binary = cv.inRange(HSV, lowerColor, upperColor)

    # 运用中值滤波去除噪声
    median = cv.medianBlur(binary, 9)

    # 得到轮廓
    contours, hierarchy = cv.findContours(median, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)
    img1 = img.copy()
    cv.drawContours(img1, contours, -1, (0, 0, 0), 20)

    # 以下是对红色激光点的处理,使用的是img1
    img2 = bg.baoguang(img1)

    b, g, r = cv.split(img2)
    r_b = g
    for i in range(len(r)):
        for j in range(len(r[0])):
            if r[i][j] <= b[i][j]:
                r_b[i][j] = 0
            else:
                r_b[i][j] = (r[i][j] - b[i][j]) * 3

    cv.threshold(r_b, 180, 255, cv.THRESH_BINARY, r_b)
    kernel = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
    dilated = cv.dilate(r_b, kernel, iterations=2)
    contours_1, hierarchy = cv.findContours(dilated, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)

    return contours + contours_1


def find(img):
    # 经过图像处理得到轮廓信息
    contours = process(img)
    # contours轮廓数据是数组，因此用len()测数组长度
    L = len(contours)
    centers = [(), ()]
    # 如果识别到的不是两个激光点，则之间返回(0, 0)，(0, 0)坐标
    if L != 2:
        print("skip")
        return (0, 0), (0, 0)

    else:
        for i in range(2):
            # cnt表示第i个白色快的轮廓信息
            cnt = contours[i]

            # 得到白色块外接圆的圆心坐标和半径
            (x, y), radius = cv.minEnclosingCircle(cnt)

            # center为圆心坐标，必须是整数
            center = (int(x), int(y))
            centers[i] = center

            # 传入圆心信息，并用十字标标在原图上
            line_color = (0, 255, 0)
            cv.line(img, (int(x) - 15, int(y)), (int(x) + 15, int(y)), line_color, 1)
            cv.line(img, (int(x), int(y) + 15), (int(x), int(y) - 15), line_color, 1)
            cv.putText(img, '{}'.format(center), (int(x) - 35, int(y) + 20), cv.FONT_HERSHEY_SIMPLEX, 0.4, line_color)

    return centers
