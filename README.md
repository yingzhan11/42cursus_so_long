计划：

# Bonus

**Make the player lose when they touch an enemy patrol.**

√ 1-获取敌人数量，敌人起始位置，敌人类型（V & H）， 敌人方向（d & l）：V方向敌人默认先向下走，H方向的敌人默认先向右走

√ 2-检查敌人密度check denisty: (number of enemy * 100) / (empty + collect + 2)

**TODO** 		3-path: 有点困难，没想好，可能用穷举法，但这样太慢了，暂时没想到更高效的方法

**TODO**	4-load enemy image, 一个enemy，只能存一个方向的图，如果分开两张tex，需要两个enemy 数组， enemy_v, enemy_h。先用同一张，后面做动画时研究只用一张tex的方法，可解决这个问题

√ 5-时间loop， 使用double mlx_get_time(void); 获取mlx里的double	delta_time;

√ 6-敌人移动，，当敌人遇到墙1或者可收集物C，改变方向。

**TODO** 7-敌人遇到玩家时，应退出游戏。目前玩家不动情况下，敌人遇到玩家，不会失败并退出，只有玩家主动移动到敌人的位置，才会loose，需要在地图上增加标记玩家的当前位置p


**Add some sprite animation.**

**Display the movement count directly on screen instead of writing it in the shell.**
