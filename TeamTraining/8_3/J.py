s1 = raw_input()
s0 = raw_input()
s2 = ''
for i in range(0, len(s0)):
	s2 = s2 + (chr(((ord(s0[i]) - ord(s1[i % len(s1)]) - 1 - 2 * ord('A')) % 26 + 26) % 26 + ord('A')))

print s2
