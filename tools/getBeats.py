from time import time
import pickle

i = raw_input()
t1 = time()
markers = []

for k in range(1,100):	
	i = raw_input()
	t = 1000*(time() - t1)
	if i == '1':
	  break
	markers.append(int(t))


with open('markers.data', 'wb') as f:
	pickle.dump(markers, f)

