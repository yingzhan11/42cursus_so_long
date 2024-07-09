计划：

# Bonus

## Make the player lose when they touch an enemy patrol.

√ 1-获取敌人数量，敌人起始位置，敌人类型（V & H）， 敌人方向（d & l）：V方向敌人默认先向下走，H方向的敌人默认先向右走

√ 2-检查敌人密度check denisty: (number of enemy * 100) / (empty + collect + 2)

**TODO** 3-path: 有点困难，没想好，可能用穷举法，但这样太慢了，暂时没想到更高效的方法

**TODO** 4-load enemy image, 一个enemy，只能存一个方向的图，如果分开两张tex，需要两个enemy 数组， enemy_v, enemy_h。先用同一张，后面做动画时研究只用一张tex的方法，可解决这个问题

√ 5-时间loop， 使用double mlx_get_time(void); 获取mlx里的double	delta_time;

√ 6-敌人移动，，当敌人遇到墙1或者可收集物C，改变方向。

√ 7-敌人遇到玩家时，退出游戏。敌人移动之后检测当前位置坐标是否与玩家当前坐标一样


## Add some sprite animation.

_**enemy animation**_

√ 1-add enemy animation, fly as time changes. cannt change dir now

√ 2-改变敌人方向，change dircetion. put enemy image in t_enemy, for each enemy. the full image for all animation in t_image. when enemy change dir, put_pixel from full enemy image in t_image.

_**player animation**_

√ 1-玩家站立动画

**TODO** 2-玩家移动动画，从此处移动到下一格，过程中动画

## Display the movement count directly on screen instead of writing it in the shell.
