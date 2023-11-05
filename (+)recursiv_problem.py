
def calculate_steps(steps:int,step_current:int,count:int,list:list):
  if step_current > steps:
    return 0
  if step_current <= steps:
      if len(list) <= steps:
        list.append(0)
      count = calculate_steps(steps,step_current+1,count,list)
      count = calculate_steps(steps,step_current+2,count,list)
  print(step_current, len(list))
  if list[step_current] > 0:
    count += list[step_current]
  else:
    if step_current == steps:
      list[step_current] = 1
      count += list[step_current]
    if list[step_current] == 0 and step_current <= steps-2:
      list[step_current] = list[step_current+1] + list[step_current+2]
    if list[step_current] == 0 and step_current > steps-2:
      list[step_current] = list[step_current+1]
  return count

def makelist(list:list,steps:int,count:int):
  if steps == count+1:
    list.append(1)
    list.append(1)
  else:
    list.append(0)
    makelist(list,steps,count+1)
    list[count] = list[count+1] + list[count+2]
  return 0

while True:
  steps = int(input("Number of steps: >>>>>"))
  list = []
  print(f"Total steps: {calculate_steps(steps,0,0,list)}")
  print(list)