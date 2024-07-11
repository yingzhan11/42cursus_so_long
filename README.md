计划：

# Bonus

## Make the player lose when they touch an enemy patrol.

√ 1-获取敌人数量，敌人起始位置，敌人类型（V & H）， 敌人方向（d & l）：V方向敌人默认先向下走，H方向的敌人默认先向右走

√ 2-检查敌人密度check denisty: (number of enemy * 100) / (empty + collect + 2)

**TODO** 3-path: 有点困难，没想好，可能用穷举法，但这样太慢了，暂时没想到更高效的方法 **有问题，huge map会显示没有valid路线，但是用manda版本是有路线的，large也有，解决了，但huge仍然有这个问题，没发现是哪里的问题。

// redraw the map, replace enemy by wall and empty

which kind of enemy is wall, which kind can be 0

enemy position and all enemy path was surroundding by 1 -> 1

middle position on path, near grid(left right for V, up down for H) has at least one is 0 or C -> 0

the end two grid of enemy path, only one near grid is 0 or C or E

√ 4-load enemy image

√ 5-时间loop， 使用double mlx_get_time(void); 获取mlx里的double	delta_time;

√ 6-敌人移动，，当敌人遇到墙1或者可收集物C，改变方向。

√ 7-敌人遇到玩家时，退出游戏。敌人移动之后检测当前位置坐标是否与玩家当前坐标一样

## Add some sprite animation.

_**enemy animation**_

√ 1-add enemy animation, fly as time changes. cannt change dir now

√ 2-改变敌人方向，change dircetion. put enemy image in t_enemy, for each enemy. the full image for all animation in t_image. when enemy change dir, put_pixel from full enemy image in t_image.

_**player animation**_

√ 1-玩家站立动画

√ 2-玩家移动动画，从此处移动到下一格，位置变化+跑步动画

√ 3-玩家方向控制

**TODO** 4-代码整理+优化

## Display the movement count directly on screen instead of writing it in the shell.

√ 1-显示步数

**TODO** 2-文字大小根据窗口大小变化，可以用mlx_resize_image()函数，但目前窗口太小时，不起作用，是尺寸传值有问题，待解决

**TODO** 1-memroy check. 

## Future

1-在文字下面增加文本框image，已做 √，**TODO** 但尺寸调整需要完善，可能会考虑去掉这个功能，以后再做

2-玩家攻击 attach
