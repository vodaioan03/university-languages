import tkinter
import customtkinter
from ui.ui import *


class GUI(UI_functions):
  
  def __init__(self):
    super().__init__()
    customtkinter.set_appearance_mode("System")
    customtkinter.set_default_color_theme("blue")
    self.__app = customtkinter.CTk()
    self.__app.geometry("720x480")
    self.__app.title("Library App")
    self.__frames = {}
    self.create_frame("MenuPrincipal")
    self.create_frame("MenuManage")
    self.create_frame("MenuSearchClients")
    self.create_frame("MenuSearchBooks")
  
  def _addframes(self):
    message = ["0.Option Menu"]
    message.append("1. Manage Clients and Books")
    message.append("2. Rent a book")
    message.append("3. Return a book")
    message.append("4. Search Clients.")
    message.append("5. Search Books.")
    message.append("6. Create Statistic")
    message.append("7. Exit")

    for each in message:
      label = customtkinter.CTkButton(self.__frames["MenuPrincipal"],text=each,command=lambda opt=each: self.input_command(opt[0]))
      label.pack()
    
    self._add_frame_for_books()
    self._add_frame_for_clients()
    self._addframe_for_manage()
  
  def _addframe_for_manage(self):
    messages = ["0. Manage Clients and Books"]
    messages.append("1. Add Client")
    messages.append("2. Add Book")
    messages.append("3. Delete Client(Only by ID)")
    messages.append("4. Delete Book(Only by ID)")
    messages.append("5. Update Client(Only by ID)")
    messages.append("6. Update Book(Only by ID)")
    messages.append("7. Show list with Clients")
    messages.append("8. Show list with Books")    
    for each in messages:
      label = customtkinter.CTkButton(self.__frames["MenuManage"],text=each,command=lambda opt=each: self._manage_menu_return(opt[0]))
      label.pack()
      
  def _add_frame_for_clients(self):
    messages = ["0. Client Search"]
    messages.append("1. From ID")
    messages.append("2. From Name")
    for each in messages:
        label = customtkinter.CTkButton(self.__frames["MenuSearchClients"],text=each,command=lambda opt=each: self._search_clients_return(opt[0]))
        label.pack()
        
  def _add_frame_for_books(self):
    messages = ["0. Book Search"]
    messages.append("1. From ID")
    messages.append("2. From Title")
    messages.append("2. From Author")
    for each in messages:
        label = customtkinter.CTkButton(self.__frames["MenuSearchBooks"],text=each,command=lambda opt=each: self._search_books_return(opt[0]))
        label.pack()
      
  def print_menu(self):
    self.show_frame("MenuPrincipal")
    pass
    
  def input_command(self,command = '') -> None:
    super()._command_proceed(command)
  
  def _print_menu_for_manage(self,command = ''):
    self.show_frame("MenuManage")
    
  def _manage_menu_return(self,command = ''):
    print(command)
    super()._manage(command)
    
  def _menu_for_search_clients(self,option = ''):
    self.show_frame("MenuSearchClients")
    
  def _search_clients_return(self,option = ''):
    return option

  def _menu_for_search_books(self,option = ''):
    self.show_frame("MenuSearchBooks")
  
  def _search_books_return(self,option = ''):
    return option
  
  def _input_id_search(self):
    return int(input("Type id for search: ").strip())

  def _input_string_search(self):
    return input("Type : ").strip()

  def _addclient(self):
    client_id = input("Client id: ").strip()
    name = input("Name for client: ").strip()
    super()._addclient_logic(client_id,name)
    
  def _addbook(self):
    book_id = input("Book id: ").strip()
    title = input("Title: ").strip()
    author = input("Author: ").strip()
    super()._addbook_logic(book_id,title,author)
    
  def _deleteclient(self):
    client_id = int(input("Client id: ").strip())
    super()._deleteclient_logic(client_id)
    
  def _deletebook(self):
    book_id = int(input("Book id: ").strip())
    super()._deletebook_logic(book_id)
    
  def _updateclient(self):
    client_id = int(input("Type id client:").strip())
    new_name = input("Type new name: ").strip()
    super()._updateclient_logic(client_id,new_name)
    
  def _updatebook(self):
    book_id = int(input("Type id for book: ").strip())
    title = input("Type new title: ").strip()
    author = input("Type new author: ").strip()
    super()._updatebook_logic(book_id,title,author)
   
  def _rent(self):
    rental_id = int(input("Rental ID: ").strip())
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    start_rent =  input("Type start date(dd.mm.yy):").strip()
    return_rent = input("Type end date(dd.mm.yy):").strip() 
    super()._rent_logic(rental_id,client_id,book_id,start_rent,return_rent)
   
  def _return_book(self):
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    super()._return_book_logic(client_id,book_id)  
    
  def _print(self,string:str):
    print(string)
    
  def back_to_main_menu(self):
    self.show_frame("MenuPrincipal")
    
  def start(self):
    super().generate_items()
    self._addframes()
    self.print_menu()
    self.__app.mainloop()
    
  def create_frame(self, frame_name):
      frame = customtkinter.CTkFrame(self.__app)
      self.__frames[frame_name] = frame

  def show_frame(self, frame_name):
      for frame in self.__frames.values():
          frame.pack_forget() 

      self.__frames[frame_name].pack() 
    

class UI(UI_functions):
  
  def __init__(self,rep,filename_books,filename_clients,filename_rentals,undo_service):
    super().__init__(rep,filename_books,filename_clients,filename_rentals,undo_service)
  
  def print_menu(self) -> None:
    print("1. Manage Clients and Books")
    print("2. Rent a book")
    print("3. Return a book")
    print("4. Search Clients.")
    print("5. Search Books.")
    print("6. Create Statistic")
    print("7. Undo")
    print("8. Redo")
    print("9. Exit")
    
  def input_command(self) -> None:
    command_inserted = input("Type the command: ").strip()
    super()._command_proceed(command_inserted)
  
  def _print_menu_for_manage(self):
    print("1. Add Client")
    print("2. Add Book")
    print("3. Delete Client(Only by ID)")
    print("4. Delete Book(Only by ID)")
    print("5. Update Client(Only by ID)")
    print("6. Update Book(Only by ID)")
    print("7. Show list with Clients")
    print("8. Show list with Books")
    input_command_for_manage = input("Type command: ").strip()
    super()._manage(input_command_for_manage)
    
  def _menu_for_search_clients(self):
    print("Search Clients")
    print("1. From ID")
    print("2. From Name")
    option = int(input("Type option search: ").strip())
    return option  

  def _menu_for_search_books(self):
    print("Search Books")
    print("1. Search from ID")
    print("2. Search from Title")
    print("3. Search from Author")
    option = int(input("Type option search: ").strip())
    return option
  
  def _input_id_search(self):
    search_id = int(input("Type id for search: ").strip())
    return search_id

  def _input_string_search(self):
    return input("Type : ").strip()

  def _addclient(self):
    client_id = input("Client id: ").strip()
    name = input("Name for client: ").strip()
    super()._addclient_logic(client_id,name)
    
  def _addbook(self):
    book_id = input("Book id: ").strip()
    title = input("Title: ").strip()
    author = input("Author: ").strip()
    super()._addbook_logic(book_id,title,author)
    
  def _deleteclient(self):
    client_id = int(input("Client id: ").strip())
    super()._deleteclient_logic(client_id)
    
  def _deletebook(self):
    book_id = int(input("Book id: ").strip())
    super()._deletebook_logic(book_id)
    
  def _updateclient(self):
    client_id = int(input("Type id client:").strip())
    new_name = input("Type new name: ").strip()
    super()._updateclient_logic(client_id,new_name)
    
  def _updatebook(self):
    book_id = int(input("Type id for book: ").strip())
    title = input("Type new title: ").strip()
    author = input("Type new author: ").strip()
    super()._updatebook_logic(book_id,title,author)
   
  def _rent(self):
    rental_id = int(input("Rental ID: ").strip())
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    start_rent =  input("Type start date(dd.mm.yy):").strip()
    return_rent = input("Type end date(dd.mm.yy):").strip() 
    super()._rent_logic(rental_id,client_id,book_id,start_rent,return_rent)
   
  def _return_book(self):
    client_id = int(input("Type client id:").strip())
    book_id = int(input("Type book id: ").strip())
    super()._return_book_logic(client_id,book_id)  
    
  def _print(self,string:str):
    print(string)
    
  def back_to_main_menu(self):
    raise ValidationException("")
    
  def start(self):
    super().generate_items()
    while self._is_running:
      self.print_menu()
      try:
        self.input_command()
      except ValidationException as e:
        print(e)
      except ValueError as e:
        print("You wrote wrong parameters.")