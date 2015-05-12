import pickle
import copy
import array
import numpy as np
import matplotlib.pyplot as plt

with open('markers.data', 'rb') as f:
	markers = pickle.load(f)

print markers
high_slots = []

for marker in markers:
 	slot = marker/100	
	high_slots.append(slot + 1)

slots = [0]*high_slots[-1]
ones = [1]*high_slots[-1]


for element in high_slots:
	slots[element-1] += 1

slots = [1] + slots
slots[-1] = 0
    
# User's errors while entering occur at the following places.
#del slots[-9]	
#del slots[94]
#del slots[28]

auto_corrs = []	 	#Autocorrelation values will be stored here
slots = np.array(slots)
shifted_slot = copy.deepcopy(slots)	#shifted_slot = slots only makes 2 pointers point to the same memory location. If slots is changed, so does shifted_slot

i = 0

####################
# 1s padding for neglecting errors of the user
####################

while i < len(slots):
  if slots[i] == 1:
	slots[i-1] = 1
	if (i+1) != len(slots):
	  slots[i+1] = 1
	  i+=1
  i+=1	

print slots 
print shifted_slot

##################
# Autocorrelation implementation
##################

for i in range(0, high_slots[-1]):
	#AND implementation
	ac = shifted_slot & slots
	
	'''
	#XOR implementation
	ac = shifted_slot ^ slots
	acn = ac ^ ones
	'''

	val = sum(ac)
	auto_corrs.append(val)
	shifted_slot = np.roll(shifted_slot,1)

arr = [ele for ele in auto_corrs if ele != 0]

print auto_corrs
print arr	# arr contains non-zero autocorrelation values

max_elem = max(arr)
max_ind = [i for i,j in enumerate(auto_corrs) if j == max_elem]		# getting locations of maximum correlation

rep = [i for i in max_ind if (i+1) in max_ind]

j=0
for i in rep:
  del auto_corrs[i-j]
  j += 1   	

print auto_corrs

################
# plotting
################

x = np.arange(len(arr))
plt.plot(x,arr,'bo')
plt.show()





