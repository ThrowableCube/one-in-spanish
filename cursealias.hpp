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

void winTitle(WINDOW *window, const char* string) { // an alias for printing titles
    box(window, 0, 0);
    wattron(window, A_REVERSE);
    mvwprintw(window, 0, 2, string);
    wattroff(window, A_REVERSE);
}