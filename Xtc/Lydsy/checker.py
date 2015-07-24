import os
import filecmp

os.system('make gen')
os.system('make std')
os.system('g++ 2653.cpp -o 2653 -Wall -lm --static -DONLINE_JUDGE')

while(True):
	print 'gen'
	os.system('./gen > A.in')
	print 'std'
	os.system('./std < A.in > std.out')
	print 'me'
	os.system('./2653 < A.in > my.out')
	if filecmp.cmp('my.out', 'std.out') == True:
		print 'Ac'
	else:
		print 'Wa'
		break