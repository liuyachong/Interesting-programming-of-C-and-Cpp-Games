import turtle

mp = turtle.Pen()
sc = turtle.Screen()
sc.tracer(0)        # 画笔追踪开关

# 定义绘制扇形函数，颜色参数设置为默认参数
def sector(r,angle = 5,color = "black"):
    mp.fillcolor(color) # 设置填充颜色
    mp.begin_fill()     # 开始填充
    mp.penup()          # 抬起画笔，但记录画笔轨迹
    mp.forward(r)
    mp.left(90)
    mp.circle(r,angle)
    mp.left(90)
    mp.forward(r)
    mp.pendown()        # 恢复画笔放下状态
    mp.end_fill()       # 结束填充
    mp.right(180)

# 设置颜色组
color_list = ["red","black","cyan","white"]

angel_a = 10    # 大角度
angel_b = 5     # 小角度
level = 8       # 循环的层数

for k in range(level):
    for i in range(360//(angel_a+angel_b)*2):
        for j in range(4):
            color = color_list[j]
            if j % 2 == 0:
                sector(50*(level+1)-k*50,angel_a,color)
            else:
                sector(50*(level+1)-k*50, angel_b, color)
    mp.right(angel_a+angel_b)   # 完成一轮绘制之后，偏转一组颜色角度的二分之一

turtle.done()
