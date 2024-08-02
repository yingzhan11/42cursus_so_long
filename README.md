# About this project

It is a small 2D game.

In the mandatory part, the player need to collect all fries then go to the exit door. 

In the bonus part, there are many enemys, the hungry seagull! If the player encounter the seagull, GAME OVER!

# How to play

1-git clone my program. The MLX42 library clone is including inside the Makefile, so you can just ```make``` the program. ```make``` for mandatory part, and ```make bonus``` for bonus part. If you make the mandatory first, when you want to try bonus game, ```make fclean``` to clear all mandatory files, then ```make bonus```, caz I use write some functions in same names, there might be some conflict if mandatory and bonus both exist.

2-contorl player with WASD, collect all delicious fries and avoid seagull.

# Demo

## Mandatory part

[so_long_mandatory.webm](https://github.com/user-attachments/assets/49360429-25c0-4891-8a2e-420d493b5479)


## Bonus part

[so_long_bonus.webm](https://github.com/user-attachments/assets/409e6195-0b8a-4aad-bcc7-7de2e2a5594b)

# Some tips to this project

1-The mandatory part is easy, I spend about 2.5 weeks to do it. The bonus part would be a little difficult on managing animation and checking the enemy path. Print string inside window is easy. The bonus part tooks me 1.5 weeks. So if you are very interested in how to make a animation, try it, it's interesting. If not, DONOT think about bonus.

2-Read the .h file of MLX42 library carefully, there are a lot of values and functions you can use directly in your code. And try the code provide in MLX42 README.d. It would save time when you start coding. And whenever you want to add some new functions or use some values, back to and search in MLX42, you might find that you don't have to write it by yourself.

3-Remember to be careful with malloc and memmory leak.

4-In the mandatory part, clip your texture files into single pieces and load they seperately into image would be eaiser (and put pixel is not allowed in mandatory part in the evaluation instruction). But in bonus animation, load the full aninmation frames texture would be better, more efficient and easy to be managed.

5-When you check the valid path of map, try the floodfill agorithm(Level4 of exam rank02)

# Problems in my bonus part

**1-Make the player lose when they touch an enemy patrol.**

The bonus part still has some small problem about how to check valid path, which not matter too much for playing.

As I set two kinds of enemy, one is marked as "V", which moves along vertical path, another one is "H", moves along horizontal path. And you can set the enemy speed in .h file.

SO, if I check all possible positions for each enemy to find a valid path (the way same as the mandatory part), sometimes it may show there is a valid path to win. But in some case like, the enemy speed is much faster than player, player cannot pass the narrow place, get collections and go back to safe place without touch any enemys.


If I consider the enemy speed and player speed in the valid path checker, it not a simple function can achieve. And in my initial plan, I want to make player attack function to kill the enemy. If I did that, there is no need to consider enemy position when check valid path.

**2-Add some sprite animation.**

Everytime the enemy move, the map grid need to be changed at the same time. So I set the enemy movement like a jump to the next cell of grid each time, not move from now cell to next cell(like player). 

**3-Display the movement count directly on screen instead of writing it in the shell.**

In MLX42, string is convert to a image then display on window. That means we can resize the string with ```mlx_resize_image()``` function.

I tried to resize the text, but meet some problem, like, when the window is too small, my resize func cannot change the text size, text would be the default size. I know the bug may at the calculation of text size. It needs too much time to fix it to prefect. So I give it up for now, maybe do it in the furture.

# Future Plan (if I want to optimize this game oneday)

1-Player can attack and kill the enemy.

2-Resize text according to the size of window.
