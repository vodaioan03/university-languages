class Book:
  def __init__(self,isbn,author,title):
    """Init class for book information

    Args:
        isbn (bool): isbn for book, need to be unique
        author (_type_): author for book
        title (_type_): title book
    """
    self.isbn = isbn
    self.author = author
    self.title = title
    
  def serialize(self):
    return {"isbn": self.isbn,
            "author": self.author,
            "title": self.title}
  