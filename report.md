#                                          泡泡堂 - 第一阶段项目报告

---

​                                                                                                                                                                                              211240094 陈卓

----

## 完成进度

- 地图类、炸弹类、玩家类、AI 均实现了必做要求
- 除了操作类全局函数，其他游戏实现均使用面向对象程序设计方法实现
- 除了前期阶段的调试性commit，具有一定数量的、分阶段的commit记录
- 代码变量名均具有实际含义

## 参考代码

- 处理闪屏问题，参考双缓存代码处理

  ~~~~c++
  #include <windows.h>
  using namespace std;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = { 0, 0 };
  SetConsoleCursorPosition( hConsole, coordScreen );
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;
  GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
  CursorInfo.bVisible = false; //隐藏控制台光标
  SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
  ~~~~

## 遇到的困难

- 多次使用 `symtem("cls")` 清屏导致控制台闪屏
- 使用`counter == ONE_SECOND` 实现计数器导致的计时不精确
- AI 实现十分困难，目前只能做到机械循环
- 某些函数的实现封装性不良好，重构时代码冗余

## 实验心得

- 在添加玩家、AI等对象时，深刻体会到面向对象程序设计方法的优越性
- 学会了分文件管理项目，使代码清晰，有层次
- 在不断完善，试验的过程中获得乐趣

## 致谢

- 郑义云、孙飞宇等同学试玩找出bug
- 徐沐杰同学对于处理闪屏问题给出的提示
- zybgg 组织的项目讲解与分析