#Find the smallest number `m` from the Fibonacci sequence, defined by `f[0]=f[1]=1`, `f[n]=f[n-1] + f[n-2]`, for `n > 2`, larger than the given natural number `n`. (e.g. `for n = 6, m = 8`).

def generateFibonacci(number:int):
  fibonacci = []
  fibonacci.append(1)
  fibonacci.append(1)
  for integer in range(2,number+1):
    fibonacci.append(fibonacci[integer-1]+fibonacci[integer-2])
  return fibonacci

def search_number(fibonacci:list, number:int):
  for integer in range(0, len(fibonacci)):
    if fibonacci[integer] > number:
      return fibonacci[integer]


while True:
  number = input("Type a number:")
  if number.strip().isnumeric():
    number = int(number)
    print("Input is correct.")
  else:
    print("Input is not correct. Type a integer number.")
    continue
  fibonacci = generateFibonacci(number)
  print(f"The smallest number is: {search_number(fibonacci,number)}")