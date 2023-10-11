#Generate the largest prime number smaller than a given natural number `n`. If such a number does not exist, a message should be displayed.
def isPrime(num:int):
  if num < 2:
    return 0
  if num > 2 and num % 2 == 0:
    return 0
  d = 3
  while d <= num // 2 :
    if num % d == 0:
      return 0
    d += 2
  return 1

def generatePrim(number:int):
  while not isPrime(number) and number > 2: 
    number -= 1
  if number >= 2:
    return number, 1
  return number,0

while True:
  number = input("Type a number:")
  if number.strip().isnumeric():
    number = int(number)
    print("Input is correct.")
  else:
    print("Input is not correct. Type a integer number.")
    continue
  generate_number , ok = generatePrim(number-1)
  if ok == 1:
    print(f"The first prime number smaller is: {generate_number}")
  else:
    print(f"Doesen't exist a prime number smaller than {number}")