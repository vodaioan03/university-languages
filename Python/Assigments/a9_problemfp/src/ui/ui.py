from repository.memory import Memory
from services.requirments import *
from domain.library import Book, Client, Rental
from ui.errors import *
from services.undo_service import *
import sys

class UI_functions:
  
  def __init__(self,rep,filename_books,filename_clients,filename_rental,undo_service):
    self._is_running = True
    self.__undo_service = undo_service
    self.__clientlogical = ClientLogic(self.__undo_service,rep,filename_clients)
    self.__bookslogical = BookLogic(self.__undo_service,rep,filename_books)
    self.__rentallogic = RentalLogic(self.__undo_service, self.__clientlogical.clientrepo, self.__bookslogical.bookrepo,rep,filename_rental)
    self.__clientlogical.update_rental_service(self.__rentallogic)
    self.__bookslogical.update_rental_service(self.__rentallogic)
    self.__commands = {"0":self.back_to_main_menu,"1":self._print_menu_for_manage,"2":self._rent,"3":self._return_book,"4":self._search_clients,"5":self._search_books,"6":self._statistics,"7":self.undo_operation,"8":self.redo_operation,"9":quit}
    self.__managecomm = {"0":self.back_to_main_menu,"1":self._addclient,"2":self._addbook,"3":self._deleteclient,"4":self._deletebook,"5":self._updateclient,"6":self._updatebook,"7":self._listclients,"8":self._listbooks,"9":self._listrentals}
    
  
  def _command_proceed(self,command:str):
    if command in self.__commands:
      self.__commands[command]()
    else:
      raise OptionError("Invalid command!")
  
  def _manage(self,command):
    if command in self.__managecomm:
      try:
        self.__managecomm[command]()
      except ValidationException as e:
        print(e)
    else:
      raise OptionError("Invalid command!")
  
  def _addclient_logic(self,client_id:str,name:str):
      self.__clientlogical.add_client([int(client_id),name])
      self._print("\nClient has been added\n")
      
  def _addbook_logic(self,book_id:str,title:str,author:str):
      self.__bookslogical.add_book([int(book_id),title,author])
      self._print("\nBook has been added\n")
      
  def _deleteclient_logic(self,client_id:int):
    self.__clientlogical.delete_client(client_id)
    self._print("\nClient has been deleted\n")
  
  def _deletebook_logic(self,book_id:int):
    self.__bookslogical.delete_book(book_id)
    self._print("\nBook has been deleted\n")
  
  def _updateclient_logic(self,client_id:int,new_name:str):
    self.__clientlogical.update_client(client_id,new_name)
    self._print("\nClient has been updated\n")
    
  def _updatebook_logic(self,book_id:int,title:str,author:str):
    self.__bookslogical.update_book(book_id,title,author)
    self._print("\nBook has been updated\n")
  
  def _listclients(self):
    clients = self.__clientlogical.show_list_with_clients()
    self._print("List with all clients: \n")
    for each in clients:
      self._print(clients[each])
      
  def _listrentals(self):
    rentals = self.__rentallogic.show_rentals()
    self._print("list with rentals \n")
    for each in rentals:
      self._print(rentals[each])
  
  def _listbooks(self):
    books = self.__bookslogical.show_list_with_books()
    self._print("List with all books: \n")
    for each in books:
      self._print(books[each])
  
  #FOR MENU
  
  def _search_clients(self):
    found = []
    try:
      option = self._menu_for_search_clients()
      if option == 1:
        search_id = self._input_id_search()
        found = self.__clientlogical.search_client_id(search_id)
      elif option == 2:
        search_name = self._input_string_search()
        found = self.__clientlogical.search_client_name(search_name)
      elif option == 0:
        self.back_to_main_menu()
      else:
        raise OptionError("Incorrect option!")
    
    except ValidationException as e:
      self._print(e)
      return
    if len(found) == 0:
      self._print("No Clients.")
      return
    self._print(f"WE found {len(found)} clients \n")
    for each in found:
      self._print(each)
  
  def undo_operation(self):
    print("undo")
    self.__undo_service.undo()
    pass
  
  def redo_operation(self):
    print("redo")
    self.__undo_service.redo()
    pass
  
  def _search_books(self):
    found = ''
    try:
      option = self._menu_for_search_books()
      if option == 1:
        search_id = self._input_id_search()
        found = self.__bookslogical.search_book_id(search_id)
      elif option == 2:
        search_title = self._input_string_search()
        found = self.__bookslogical.search_book_title(search_title)
      elif option == 3:
        search_author = self._input_string_search()
        found = self.__bookslogical.search_book_author(search_author)
      elif option == 0:
        self.back_to_main_menu()
      else:
        raise OptionError("Incorrect option!")
    except ValidationException as e:
      self._print(e)
      return
    if len(found) == 0:
      self._print("No Books.")
      return
    self._print(f"WE found {len(found)} books \n")
    for each in found:
      self._print(each)
      
  
  def _statistics(self):
    result_books = self.__rentallogic.statistics_for_books()
    result_clients = self.__rentallogic.statistics_for_client()
    result_author = self.__rentallogic.statistics_for_authors()
    
    self._print("Top rented Books \n")
    for each in result_books:
      self._print(each)
  
    self._print("\nTop Clients \n")
    for each in result_clients:
      self._print(each)
      
    self._print("\nTop Authors \n")
    for each in result_author:
      self._print(each)

  def __verify_date(self,string:str):
    months = {"01":31,"02":28,"03":31,"04":30,"05":31,"06":30,"07":31,"08":31,"09":30,"10":31,"11":30,"12":31}
    string_splitted = string.split(".")
    if len(string_splitted) != 3:
      raise OptionError("The date is incorrect!")
    if not string_splitted[1].strip() in months:
      raise OptionError("The month is incorrect! Please type (01-12)")
    if months[string_splitted[1]] < int(string_splitted[0].strip()):
      raise OptionError("The date is incorrect! Please type the correct day. Between 01-31")
    if int(string_splitted[2].strip()) < 2023:
      raise OptionError("Incorrect year. Type the correct date.")
  
  def _rent_logic(self,rental_id:int,client_id:int,book_id:int,start_rent:str,return_rent:str):
    
    self.__verify_date(start_rent)
    self.__verify_date(return_rent)
    self.__rentallogic.rental_book(rental_id,client_id,book_id,start_rent,return_rent)
  
  def _return_book_logic(self,client_id:int,book_id:int):
    self.__rentallogic.return_book(client_id,book_id)
  
  
  
  def generate_items(self):
    #self.__clientlogical.add_clients()
    #self.__bookslogical._addbooks()
    #self.__rentallogic.add_rentals()
    pass