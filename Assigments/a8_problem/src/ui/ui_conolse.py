from repository.memory import Memory
from services.requirments import *
from domain.library import Book, Client, Rental
from ui.errors import *

class UI:
  
  def __init__(self) -> None:
    self.__is_running = True
    self.__clientlogical = ClientLogic()
    self.__bookslogical = BookLogic()
    self.__rentallogic = RentalLogic(self.__clientlogical.clientrepo, self.__bookslogical.bookrepo)
    self.__commands = {"1":self.__print_menu_for_manage,"2":self.__rent,"3":self.__return_book,"4":self.__search_clients,"5":self.__search_books,"6":self.__statistics,"7":quit}
    self.__managecomm = {"1":self.__addclient,"2":self.__addbook,"3":self.__deleteclient,"4":self.__deletebook,"5":self.__updateclient,"6":self.__updatebook,"7":self.__listclients,"8":self.__listbooks,"9":self.__listrentals}
  
  def __print_menu(self) -> None:
    print("1. Manage Clients and Books")
    print("2. Rent a book")
    print("3. Return a book")
    print("4. Search Clients.")
    print("5. Search Books.")
    print("6. Create Statistic")
    print("7. Exit")
    
  def __input_command(self) -> None:
    input_comm = input("Type the command: ").strip()
    self.__command_proceed(input_comm)
    
  def __command_proceed(self,command):
    if command in self.__commands:
      self.__commands[command]()
    else:
      raise OptionError("Invalid command!")
  
  def __print_menu_for_manage(self):
    print("1. Add Client")
    print("2. Add Book")
    print("3. Delete Client(Only by ID)")
    print("4. Delete Book(Only by ID)")
    print("5. Update Client(Only by ID)")
    print("6. Update Book(Only by ID)")
    print("7. Show list with Clients")
    print("8. Show list with Books")
    input_command_for_manage = input("Type command: ").strip()
    self.__manage(input_command_for_manage)
  
  def __manage(self,command):
    if command in self.__managecomm:
      try:
        self.__managecomm[command]()
      except ValidationException as e:
        print(e)
    else:
      raise OptionError("Invalid command!")
  
  def __addclient(self):
      client_id = input("Client id: ").strip()
      name = input("Name for client: ").strip()
      self.__clientlogical.add_client([int(client_id),name])
      
  def __addbook(self):
      book_id = input("Book id: ").strip()
      title = input("Title: ").strip()
      author = input("Author: ").strip()
      self.__bookslogical.add_book([int(book_id),title,author])
      
  def __deleteclient(self):
    client_id = int(input("Client id: ").strip())
    self.__clientlogical.delete_client(client_id)
  
  def __deletebook(self):
    book_id = int(input("Book id: ").strip())
    self.__bookslogical.delete_book(book_id)
  
  def __updateclient(self):
    client_id = int(input("Type id client:").strip())
    new_name = input("Type new name: ").strip()
    self.__clientlogical.update_client(client_id,new_name)
    
  def __updatebook(self):
    book_id = int(input("Type id for book: ").strip())
    title = input("Type new title: ").strip()
    author = input("Type new author: ").strip()
    self.__bookslogical.update_book(book_id,title,author)
  
  def __listclients(self):
    clients = self.__clientlogical.show_list_with_clients()
    print("List with all clients: \n")
    for each in clients:
      print(clients[each])
      
  def __listrentals(self):
    rentals = self.__rentallogic.show_rentals()
    print("list with rentals \n")
    for each in rentals:
      print(rentals[each])
  
  def __listbooks(self):
    books = self.__bookslogical.show_list_with_books()
    print("List with all books: \n")
    for each in books:
      print(books[each])
  
  #FOR MENU
  
  def __menu_for_search_clients(self):
    print("Search Clients")
    print("1. From ID")
    print("2. From Name")
    option = int(input("Type option search: ").strip())
    return option
  
  def __search_clients(self):
    found = []
    try:
      option = self.__menu_for_search_clients()
      if option == 1:
        search_id = int(input("Type id for search: ").strip())
        found = self.__clientlogical.search_client_id(search_id)
      elif option == 2:
        search_name = input("Type name for search: ").strip()
        found = self.__clientlogical.search_client_name(search_name)
      else:
        raise OptionError("Incorrect option!")
    except ValidationException as e:
      print(e)
    if len(found) == 0:
      print("No clients found.")
      return
    print(f"WE found {len(found)} clients \n")
    for each in found:
      print(each)
  
  def __menu_for_search_books(self):
    print("Search Books")
    print("1. Search from ID")
    print("2. Search from Title")
    print("3. Search from Author")
    option = int(input("Type option search: ").strip())
    return option
  
  def __search_books(self):
    found = ''
    try:
      option = self.__menu_for_search_books()
      if option == 1:
        search_id = int(input("Type id for search: ").strip())
        found = self.__bookslogical.search_book_id(search_id)
      elif option == 2:
        search_title = input("Type title for search: ").strip()
        found = self.__bookslogical.search_book_title(search_title)
      elif option == 3:
        search_author = input("Type author for search: ").strip()
        found = self.__bookslogical.search_book_author(search_author)
      else:
        raise OptionError("Incorrect option!")
    except ValidationException as e:
      print(e)
    if len(found) == 0:
      print("No books found.")
      return
    print(f"WE found {len(found)} books \n")
    print(found)
    for each in found:
      print(each)
      
  
  def __statistics(self):
    result_books = self.__rentallogic.statistics_for_books()
    result_clients = self.__rentallogic.statistics_for_client()
    result_author = self.__rentallogic.statistics_for_authors()
    
    print("Top rented Books \n")
    for each in result_books:
      print(each)
  
    print("\nTop Clients \n")
    for each in result_clients:
      print(each)
      
    print("\nTop Authors \n")
    for each in result_author:
      print(each)

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
  
  def __rent(self):
    rental_id = int(input("Rental ID: ").strip())
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    start_rent =  input("Type start date(dd.mm.yy):").strip()
    return_rent = input("Type end date(dd.mm.yy):").strip()
    self.__verify_date(start_rent)
    self.__verify_date(return_rent)
    self.__rentallogic.rental_book(rental_id,client_id,book_id,start_rent,return_rent)
  
  def __return_book(self):
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    self.__rentallogic.return_book(client_id,book_id)
  
  
  def start(self):
    self.__bookslogical._addbooks()
    self.__clientlogical.add_clients()
    self.__rentallogic.add_rentals()
    while self.__is_running:
      self.__print_menu()
      try:
        self.__input_command()
      except ValidationException as e:
        print(e)
      except ValueError as e:
        print("You wrote wrong parameters.")