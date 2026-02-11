import curses
import random
import time


def main(stdscr):
    curses.curs_set(0)
    stdscr.nodelay(True)
    stdscr.timeout(1)

    height = 20
    width = 40
    basket_width = 7
    basket_x = width // 2 - basket_width // 2

    score = 0
    life = 5

    fall_speed = 0.25     # candy falling speed (seconds)
    input_delay = 0.01    # fast input refresh

    while life > 0:

        candy_x = random.randint(1, width - 2)
        candy_y = 1

        last_fall_time = time.time()

        while candy_y <= height:

            key = stdscr.getch()

            # fast basket movement
            if key in (ord('a'), ord('A')) and basket_x > 1:
                basket_x -= 1
            elif key in (ord('d'), ord('D')) and basket_x + basket_width < width:
                basket_x += 1
            elif key in (ord('q'), ord('Q')):
                return

            # candy movement based on time
            current_time = time.time()
            if current_time - last_fall_time >= fall_speed:
                candy_y += 1
                last_fall_time = current_time

            stdscr.clear()

            # borders
            for x in range(width):
                stdscr.addch(0, x, '-')
                stdscr.addch(height + 1, x, '-')

            # candy
            if candy_y <= height:
                stdscr.addch(candy_y, candy_x, '0')

            # basket
            for i in range(basket_width):
                stdscr.addch(height, basket_x + i, '#')

            # info
            stdscr.addstr(height + 3, 0, f"Score: {score}   Life: {life}")
            stdscr.addstr(height + 4, 0, "A: Left   D: Right   Q: Quit")

            stdscr.refresh()
            time.sleep(input_delay)

        # check catch
        if basket_x <= candy_x < basket_x + basket_width:
            score += 1
            if fall_speed > 0.08:
                fall_speed -= 0.01   # increase difficulty
        else:
            life -= 1

    stdscr.clear()
    stdscr.addstr(10, 10, "GAME OVER")
    stdscr.addstr(12, 10, f"Final Score: {score}")
    stdscr.refresh()
    time.sleep(2)


curses.wrapper(main)
