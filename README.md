# DayCount
练手项目——倒数日App

**程序不会以任何形式出售，任何问你要钱的都是骗子（真的有人会拿这一堆bug的程序去卖吗）
**转载注明原作者
**BUG很多，只是个人练手项目，轻点喷
**更新周期较长（学生党）

目前已知的bug和问题：
1、拖动控件时坐标会有偏差
2、鼠标穿透透明背景直接点到桌面，我因此弄了_sleep()函数以免导致交互不友好，但是由于是单线程的特性，会导致卡顿
3、拖动控件时鼠标定位有问题
4、使用某些背景图片时会导致程序性能问题（交互有延迟）
5、选择背景图片并按下保存按钮后，默认不会刷新背景图，但是此时点击调整控件位置按钮就会马上更新程序背景图，原理应该是点击了调整控件位置按钮后再次触发了一次paintEvent事件
6、变量名起的不太友好