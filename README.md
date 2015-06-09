This file contains files and docs for the hardware
===
Correlation is a degree of similarity between two entities, like waveforms, datasets, etc. A high value of correlation means that the two entities being compared are very similar. 

Autocorrelation is comparing an entity with a scaled, compressed, shifted version of itself. 

Preprocessing involves quantisation and discretisation. User entered markers(beats) are recorded. Time is divided into 100ms slots. One marker would fall within one 100ms slot. It can be safely assumed that no 2 markers lie in the same 100ms slot. Now we have a set of 100ms slots some of which contain a marker. The slots with a marker are assigned a '1' (HIGH) value. Others '0' (LOW). Thus, we have metadata of the song, which is essentially a binary array. 
   
The motivation behind using autocorrelation after this for pattern recognition is straightforward. The process would justify it further. 
* Make two copies of the metadata(binary array)
* One remains static, and the other is 'rotated' by applying the rule arr[i] = arr[i-1] recursively for each element. The last element will be 'rolled over' and will occupy the first postion in the array.
* Now the two arrays are compared through logical operations. There are two ways to do this:
	1. Perform a bitwise-AND operation on the two arrays. The resulting array will be of the same dimension as the original array. Now add all elements of this array. In essence, count the number of 'HIGH's in it. This sum is the correlation value for this iteration. Compute for each iterative rotation and store these in a correlation_array. The highest values of the corelation_array are the iterations at which the two arrays are most similar. 
	2. Perform a bitwise-XNOR operation on the two arrays. The sum of the result is also a correlation_array.
The two methods are infact one and the same. The 2nd is shifted from the first by a finite value. 

This works because the points where the correlation_array peaks denotes that the two beats have synchronised. An observation of the 2nd array placed against the 1st at these peak points will drive the concept home. 