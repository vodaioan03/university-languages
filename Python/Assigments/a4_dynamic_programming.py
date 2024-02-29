#3. Given the set of positive integers `S`, partition this set into two subsets `S1` and `S2` so that the difference between the sum of the elements in `S1` and `S2` is minimal. For example, for set `S = { 1, 2, 3, 4, 5 }`, the two subsets could be `S1 = { 1, 2, 4 }` and `S2 = { 3, 5 }`. Display at least one of the solutions.

import copy

def dynamic_program(initial_list:list,length:int):
  list_of_num = copy.deepcopy(initial_list)
  sum_of_list = sum(list_of_num)
  dp = [[0 for i in range(sum_of_list+1)] for j in range(length+1)]
  for i in range(length+1):
    dp[i][0] = True
  for j in range(1,sum_of_list+1):
    dp[0][j] = False
  for i in range(1,length+1):
    for j in range(1,sum_of_list+1):
      dp[i][j]=dp[i-1][j]
      if list_of_num[i-1]<=j:
        dp[i][j] |= dp[i-1][j-list_of_num[i-1]]
  sum_first_sublist = -1
  for i in range(sum_of_list // 2, -1, -1):
    if dp[length][i] == True:
      sum_first_sublist = i
      break
  sum_second_sublist = sum_of_list - sum_first_sublist
  first_sublist = []
  second_sublist = []
  count = 0
  while sum_first_sublist > 0:
    if dp[count][sum_first_sublist] == True and list_of_num[count-1] != -1:
      first_sublist.append(list_of_num[count-1])
      sum_first_sublist -= list_of_num[count-1]
      list_of_num[count-1] = -1
      count = -1
    count += 1
  count = 0
  while sum_second_sublist > 0:
    if dp[count][sum_second_sublist] == True and list_of_num[count-1] != -1:
      second_sublist.append(list_of_num[count-1])
      sum_second_sublist -= list_of_num[count-1]
      count = -1
    count += 1
  first_sublist.reverse()
  second_sublist.reverse()
  return first_sublist, second_sublist

def sort_list(unsorted_list:list):
  for i in range(len(unsorted_list)):
    for j in range(i, len(unsorted_list)):
      if unsorted_list[j] < unsorted_list[i]:
        unsorted_list[i] , unsorted_list[j] = unsorted_list[j], unsorted_list[i]
  return unsorted_list

def naive_program(list_of_num:list):
  sorted_list = sort_list(list_of_num)
  subset_one = []
  subset_two = []
  sum_one, sum_two = 0, 0
  counter = len(sorted_list) - 1
  while counter >= 0:
    if sum_one < sum_two:
      sum_one += int(sorted_list[counter])
      subset_one.append(sorted_list[counter])
    else:
      sum_two += int(sorted_list[counter])
      subset_two.append(sorted_list[counter])
    counter -= 1
  subset_one.reverse()
  subset_two.reverse()
  return subset_one,subset_two 

while True:
  given_list = []
  input_list = input("Type the list: ").strip()
  given_list = input_list.split()
  for i in range(len(given_list)):
       given_list[i] = int(given_list[i])
  first_sublist,second_sublist = dynamic_program(given_list,len(given_list)) 
  print(f"For Dynamic Solution: \n Subset one: \n {first_sublist} \nSubset two: \n {second_sublist} \n") 
  subs_one,subs_two = naive_program(given_list)
  print(f"For Naive Solution: \n Subset one: \n {subs_one} \nSubset two: \n {subs_two}")  