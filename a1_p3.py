#12. Determine the age of a person, in number of days. Take into account leap years, as well as the date of birth and current date `(year, month, day)`. Do not use Python's inbuilt date/time functions.

def is_lapyear(year:int):
  if year % 4 == 0:
    if year % 400 == 0:
      return 0
    return 1
  return 0

def is_valid(year:str, month:str, day:str):
  if year.strip().isnumeric() and month.strip().isnumeric() and day.strip().isnumeric():
    print("Input is correct.")
    return 1
  else:
    print("Input is not correct. Type a integer number.")
    return 0
  
def verify_date(year:int, month:int, day:int):
  current_year, current_month, current_day = 2023, 10, 10

  if current_year < year:
    print("The date is not good.")
    return 0
  if current_year == year:
    if current_month == month:
      if current_day > day:
          print("The date is not good.")
          return 0
    elif current_month > month:
      print("The date is not good.")
      return 0
  return 1

def calculate_day(year:int, month:int, day:int):
  current_year, current_month, current_day = 2023, 10, 10
  days = 0
  if current_year > year:
    for i in range(month, 13):
      if i == 2:
        if is_lapyear(year):
          days += 29 - day
          
        else:
          days += 28 - day
      elif i == 4 or i == 6 or i == 9 or i == 11:
        days += 30 - day
        
      else:
        days += 31 - day
        
      day = 0
  year += 1
  month = 0
  day = 0
  if day == 0 and month == 0:
    for i in range(year, current_year):
      if is_lapyear(year):
        days += 366
        
      else:
        days += 365
       
      year += 1
  if year == current_year:
    for i in range(1, current_month):
      if i == 2:
        if is_lapyear(year):
          days += 29
          
        else:
          days += 28
          
          
      elif i == 4 or i == 6 or i == 9 or i == 11:
        days += 30
        
      else:
        days += 31 
        
  if current_year == year and current_month == month  or month == 0 and day == 0:
    return days
  else:
    return days+current_day

while True:
  current_year, current_month, current_day = 2023, 10, 10
  year = input("Type the year of birth: ")
  month = input("Type the month of birth: ")
  day = input("Type the day of birth: ")
  if not is_valid(year, month, day):
    continue
  
  year = int(year)
  month = int(month)
  day = int(day)
  if not verify_date(year, month, day):
    continue
  print(calculate_day(year,month,day))
  
