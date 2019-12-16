# SmartSnake

## C语言程序设计课程设计

### 游戏规则
+ 食物：蛇吃到之后，身体**增加一个单位长度**。
+ 地雷：蛇吃到后会被**炸掉一半的长度**，只剩下一个头结点的时候，直接死亡，**游戏结束**。
+ 毒草每次出现多根，一段时间后会消失，蛇吃到**减少一个单位长度**。
+ 撞到墙会死亡，**游戏结束**。
+ 身体达到一定长度的时候，**游戏胜利**，进入下一关。

### 碰撞检测边界设定
蛇的头结点是圆
地雷是圆
墙，食物，还有毒草和智慧草是矩形