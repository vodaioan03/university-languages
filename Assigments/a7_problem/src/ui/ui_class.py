from src.services.requirments import *
import os
class Tests:
  
  def __init__(self,rep,filename) -> None:
    self.rep = rep
    self.filename = filename
    self.logic = LogicalThings(self.rep,self.filename)
    pass
  
  def test_for_add(self):
    self.logic.add_book("001","marcel ciolacu","maris")
    self.logic.add_book("002","marcel ciolacu","maris 2")
    self.logic.add_book("003","marcel ciolacu","maris 213 r")
    self.logic.add_book("004","marcel ciolacu","maris  ")
    self.logic.add_book("005","marcel ciolacu","maris weqeqw 2 123 dff wd qw dd")
    self.logic.add_book("006","asta nu e marcel ciolacu","Titlu de smecher de barosa")
    self.logic.display_list_of_books()
    self.logic.filter_list('maris')
    print("dupa del de title")
    self.logic.display_list_of_books()
    self.logic.undo_last_operation()
    print("dupa primul undo")
    self.logic.display_list_of_books()


class UI:
  
  def __init__(self,rep,filename,test_filename):
    self.__start = True
    self.__rep = rep
    self.__test_filename = test_filename
    self.__filename = filename
    self.__logic = LogicalThings(self.__rep,self.__filename)
    self.__checks = VerifyInput(self.__logic)
    #self.__tests = Tests(self.__rep,self.__test_filename)
    #self.__tests.test_for_add()
    self.__add_values_at_start()
      
  
  #ONLY FOR TESTING NOW
  def __add_values_at_start(self):
    self.__logic.add_book("001","marcel ciolacu","maris")
    self.__logic.add_book("002","marcel ciolacu","maris 2")
    self.__logic.add_book("003","marcel ciolacu","maris 213 r")
    self.__logic.add_book("004","marcel ciolacu","maris  ")
    self.__logic.add_book("005","marcel ciolacu","maris weqeqw 2 123 dff wd qw dd")
    self.__logic.add_book("006","asta nu e marcel ciolacu","Titlu de smecher de barosa")
  
  def start(self):
    while self.__start:
      self.print_menu()
      try:
        self.input_value()
      except ValueError as e:
        print(e)
      
  def print_menu(self):
    print("\nLibrary Menu")
    print("1. Add a book.")
    print("2. Display the list of books.")
    print("3. Filter the book! Book titles starting with a given word are deleted from the list ")
    print("4. Undo the last operation that modified program data.")
    print("5. Exit")
    
  def input_value(self):
    option = int(input("Choose option: ").strip())
    if not option in [1,2,3,4,5]:
      raise ValueError("Invalid option.")
    self.proceed_value(option)
  
  def proceed_value(self,option):
    if option == 5:
      print("Program is stopping...")
      self.__start = False
    elif option == 1:
      input_isbn = input("Type isbn: ").strip() # Must be unique
      input_author = input("Type author: ").strip()
      input_title = input("Type title: ").strip()
      try:
        self.__checks.verify_add_Book(input_isbn)
        self.__logic.add_book(input_isbn,input_author,input_title)
      except ValueError as e:
        print(e)
    elif option == 2:
      try:
        self.__checks.verify_display()
        self.__logic.display_list_of_books()
      except ValueError as e:
        print(e)
    elif option == 3:
      input_title = input("Type title for delete: ").strip()
      try: 
        self.__checks.verify_filter(input_title)
        self.__logic.filter_list(input_title)
      except ValueError as e:
        print(e)
    elif option == 4:
      try:
        self.__checks.verify_undo()
        self.__logic.undo_last_operation()
      except ValueError as e:
        print(e)
      
  
  
# Manage a list of books. Each book has an `isbn` (string, unique), an `author` and a `title` (strings). Provide the following features:
# 1. Add a book. Book data is read from the console.
# 2. Display the list of books.
# 3. Filter the list so that book titles starting with a given word are deleted from the list.
# 4. Undo the last operation that modified program data. This step can be repeated. The user can undo only those operations made during the current run of the program.
