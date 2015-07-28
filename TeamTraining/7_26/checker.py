import os
import filecmp

os.system('g++ gen.cpp -o gen')
os.system('g++ J_std.cpp -o std -O2')
os.system('g++ J.cpp -o J -O2')

while(True):
	os.system('./gen > J.in')
	os.system('./J < J.in > J.out')
	os.system('./std < J.in > std.out')
	if filecmp.cmp('J.out', 'std.out') == True:
		print 'Ac'
	else:
		print 'Wa'
		break
