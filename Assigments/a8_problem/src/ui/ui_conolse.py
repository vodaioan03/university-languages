from repository.memory import Memory, RepositoryError
from services.requirments import LogicalThings
from domain.library import Book, Client, Rental

class UI:
  
  def __init__(self) -> None:
    self.__is_running = True
    self.__logical = LogicalThings()
    self.__commands = {"1":self.__print_menu_for_manage,"2":self.__rent,"3":self.__return_book,"4":self.__search,"5":self.__statistics,"6":quit}
    self.__managecomm = {"1":self.__addclient,"2":self.__addbook,"3":self.__deleteclient,"4":self.__deletebook,"5":self.__updateclient,"6":self.__updatebook,"7":self.__listclients,"8":self.__listbooks,"9":self.__listrentals}
  
  def __print_menu(self) -> None:
    print("1. Manage Clients and Books")
    print("2. Rent a book")
    print("3. Return a book")
    print("4. Search for clients or books.")
    print("5. Create Statistic")
    print("6. Exit")
    
  def __input_command(self) -> None:
    input_comm = input("Type the command: ")
    self.__command_proceed(input_comm)
    
  def __command_proceed(self,command):
    if command in self.__commands:
      self.__commands[command]()
    else:
      raise ValueError("Invalid command!")
  
  def __print_menu_for_manage(self):
    print("1. Add Client")
    print("2. Add Book")
    print("3. Delete Client(Only by ID)")
    print("4. Delete Book(Only by ID)")
    print("5. Update Client(Only by ID)")
    print("6. Update Book(Only by ID)")
    print("7. Show list with Clients")
    print("8. Show list with Books")
    input_command_for_manage = input("Type command: ")
    self.__manage(input_command_for_manage)
  
  def __manage(self,command):
    if command in self.__managecomm:
      try:
        self.__managecomm[command]()
      except RepositoryError as e:
        print(e)
    else:
      raise ValueError("Invalid command!")
  
  def __addclient(self):
      client_id = input("Client id: ")
      name = input("Name for client: ")
      self.__logical.add_client([int(client_id),name])
      
  def __addbook(self):
      book_id = input("Book id: ")
      title = input("Title: ")
      author = input("Author: ")
      self.__logical.add_book([int(book_id),title,author])
      
  def __deleteclient(self):
    client_id = int(input("Client id: "))
    self.__logical.delete_client(client_id)
  
  def __deletebook(self):
    book_id = int(input("Book id: "))
    self.__logical.delete_book(book_id)
  
  def __updateclient(self):
    client_id = int(input("Type id client:"))
    new_name = input("Type new name: ")
    self.__logical.update_client(client_id,new_name)
    
  def __updatebook(self):
    book_id = int(input("Type id for book: "))
    title = input("Type new title: ")
    author = input("Type new author: ")
    self.__logical.update_book(book_id,title,author)
  
  def __listclients(self):
    clients = self.__logical.show_list_with_clients()
    print("List with all clients: \n")
    for each in clients:
      print(clients[each])
      
  def __listrentals(self):
    rentals = self.__logical.show_rentals()
    print("list with rentals \n")
    for each in rentals:
      print(rentals[each])
  
  def __listbooks(self):
    books = self.__logical.show_list_with_books()
    print("List with all books: \n")
    for each in books:
      print(books[each])
  
  #FOR MENU
  def __search(self):
    pass
  
  def __rent(self):
    rental_id = int(input("Rental ID: "))
    client_id = int(input("Type client id:"))
    book_id = int(input("Type book id: "))
    start_rent =  input("Type start date(dd.mm.yy):")
    return_rent = input("Type end date(dd.mm.yy):")
    self.__logical.rental_book(rental_id,client_id,book_id,start_rent,return_rent)
  
  def __statistics(self):
    pass
  
  def __return_book(self):
    pass
  
  
  
  def start(self):
    while self.__is_running:
      self.__print_menu()
      try:
        self.__input_command()
      except ValueError as e:
        print(e)