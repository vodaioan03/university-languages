#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

from ui import *

##de retestat tot
# - Provide **specifications** for all non-UI functions (except getters and setters), and tests for all non-UI functions related to functionalities **(A)** and **(B)**
# - Have at least 10 randomly generated items in your application at program startup
def start():
  show_menu_for_help()
  history_of_commands = generate_history_command()
  while True:
    list_of_contestants = copy(history_of_commands[-1])
    input_command(history_of_commands,list_of_contestants)

if __name__ == "__main__":
  start()
  pass