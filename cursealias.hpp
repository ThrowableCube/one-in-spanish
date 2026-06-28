void Sblink(WINDOW *window, int yPos, int xPos, const char* string) { // an alias for blinking text :3
    wattron(window, A_REVERSE);
    mvwprintw(window, yPos, xPos, string);
    refresh();
    wrefresh(window);
    napms(50);
    wattroff(window, A_REVERSE);
    mvwprintw(window, yPos, xPos, string);
    wrefresh(window);
}