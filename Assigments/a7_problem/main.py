from src.ui.ui_class import *

if __name__ == "__main__":
#  rep = 'Memory'
  rep = 'Text'
#  rep = 'Pickle'
  filename = "C:\\Users\\vodai\\OneDrive\\Desktop\\CS 2023 SEM 1\\FP 2023\\a7-vodaioan03\\src\\repository\\input.txt"
  test_filename = "C:\\Users\\vodai\\OneDrive\\Desktop\\CS 2023 SEM 1\\FP 2023\\a7-vodaioan03\\src\\repository\\test.txt"
  ui = UI(rep,filename,test_filename)
  ui.start()