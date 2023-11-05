#The sequence a = a1, ..., an with integer elements is given. Determine all strictly increasing subsequences of sequence a (conserve the order of elements in the original sequence).

def print_solution(solution_list:list, step:int):
  for i in range(step+1):
    print(solution_list[i], end=' ') 
  print("")

def recursive_version(given_list:list, solution_list:list, step:list, step_in_list:int): # 2^n
  for i in range(step_in_list,len(given_list)):
    while len(solution_list) > step:
      del solution_list[len(solution_list)-1]
    solution_list.append(given_list[i])
    if step+1 == len(solution_list) and step > 0:
      if solution_list[step-1] < solution_list[step]:
        print(solution_list)
        recursive_version(given_list, solution_list, step + 1,i)
    elif step == 0:
      print(solution_list)
      recursive_version(given_list, solution_list, step + 1,i)

def iterative_version(given_list:list): # 2^n
    solution_list = [[]]
    for number in given_list:
        new_solution = []
        for subseq in solution_list:
            if not subseq or number > subseq[-1]:
                new_subseq = subseq + [number]
                new_solution.append(new_subseq)
        solution_list.extend(new_solution)
    return solution_list

while True:
  length_of_list = int(input("Type length of list: ").strip())
  given_list = []
  input_list = input("Type the list: ").strip()
  given_list = input_list.split()
  while len(given_list) > length_of_list:
    del given_list[len(given_list) - 1]
  recursive_version(given_list, [], 0,0)
  print("Iterative: \n")
  subsequences_list = iterative_version(given_list)
  for subseq in subsequences_list:
     if len(subseq) > 0:
        print(subseq)