import serial


# 串口打开函数
def open_ser():
    port = 'COM4'  # 串口号
    saturate = 9600  # 波特率
    try:
        ser = serial.Serial(port, saturate, timeout=2)
        if ser.isOpen():
            print("串口打开成功")
            return ser
    except Exception as exc:
        print("串口打开异常", exc)


# 数据发送
def send_msg(ser, send_datas):
    try:
        # send_datas = input("请输入要发送的数据:\n")
        ser.write(str(send_datas + '\r\n').encode("gbk"))
        print('-' * 80)
        print("已发送数据:")
        print(send_datas)
        print('-' * 80)
        # send_datas1 = 875
        # ser.write(str(send_datas1).encode("gbk"))
        # print("已发送数据:", send_datas1)
    except Exception as exc:
        print("发送异常", exc)


# 接收数据
def read_msg(ser):
    try:
        print("等待接收数据......")
        while True:
            data = ser.read(ser.in_waiting).decode('gbk')
            if data != '':
                break
        print('-' * 80)
        print("已接受到数据:")
        print(data)
        print('-' * 80)
    except Exception as exc:
        print("读取异常", exc)


# 关闭串口
def close_ser(ser):
    try:
        ser.close()
        if ser.isOpen():
            print("串口未关闭")
        else:
            print("串口已关闭")
    except Exception as exc:
        print("串口关闭异常", exc)


# if __name__ == '__main__':
#     ser = None
#     open_ser()  # 打开串口
#
#     while 1:
#         print('----------请选择你要进行的操作----------')
#         print('---1:发送数据--2:接收数据--3:关闭串口---')
#         op = input('请输入:')
#         if op == '1':
#             send_msg()  # 写数据
#         if op == '2':
#             read_msg()  # 读数据
#         if op == '3':
#             close_ser()  # 关闭串口
#             break