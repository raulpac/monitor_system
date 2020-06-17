#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "iostream"

using std::cout;


int main() {
  System system;
  
  NCursesDisplay::Display(system);

}