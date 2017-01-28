import argparse

def sanitize(filename):
	f = open(filename).read().split('\n')
	newF = open("cleaned.cpp",'w')
	lineNumber = 0
	print("BEGIN")
	while(lineNumber != (len(f)-1)):
		if(len(f[lineNumber]) >80):
			#if the current line contains three === or a pipe
			#figure out how much to subtract, plus one extra
			#from the beginning to the end, and add 1 pip to the end
			x = ['===','|']
			if('===' in f[lineNumber]):
				
				cleaned_up = f[lineNumber][:79] + '|'
				print(cleaned_up, file=newF)
			
			elif('BinTree::' in f[lineNumber]):
				#X is the index
				#f[X] access the list at X index
				#f[X][X] access the string at X index, and the current substring
				highest_index_of_white_space = f[lineNumber].rfind(' ')
				over = f[lineNumber][highest_index_of_white_space:]
				cleaned_up = f[lineNumber][:highest_index_of_white_space]
				print(cleaned_up, file=newF)
				print(over, file=newF)
			else:
				#for all othe lines over 8- characters, typlically
				#these include, text, comments or function def
				#look for the most recent white space and print that
				#over to the next line.
				#string.isaplha() return sif someting is alpha
				#isdigit() 
				

				highest_index_of_white_space = f[lineNumber].rfind(' ')
				over = "//" + f[lineNumber][highest_index_of_white_space:]
				cleaned_up = f[lineNumber][:highest_index_of_white_space]
				print(cleaned_up, file=newF)
				print(over, file=newF)
		else:

			print(f[lineNumber], file=newF)
		lineNumber+=1
	newF.close()
	print("DONE")

def testArgs1(hello):
	print("YOU GAB ME : %s" % hello)

def testArgs(helllo, you):
	print("This is what you give me %s AND %s" % (helllo, you))


def checkLinesGreaterThan(fileName,lineLimit):

	f = open(fileName).read().split('\n')
	lineNumber = 0
	while(lineNumber != (len(f)-1)):
		if(len(f[lineNumber]) > lineLimit):
			print("[ %s ] %s " % ( lineNumber, f[lineNumber]))
		lineNumber+=1

def main():
	"""
	parser = argparse.ArgumentParser(description = "Santitize your .cpp files")
	
	subparser = parser.add_subparsers()

	test1 = subparser.add_parser('test1')
	test1.add_argument('dddddd')
	test1.set_defaults(func=testArgs1)

	args = parser.parse_args()
	args.func(args)
	"""
	checkLinesGreaterThan("bintree.h",80)
	#sanitize("bintree.cpp")

	#parser.add_argument('integers', metavar='-v', type=str, nargs="+",
	#help="somet stuff")
	#parser.add_argument("--line-check", type=checkLinesGreaterThan,
	#action="store", help="Check lines over 80 characters")
	#parser.add_argument("test", help="Check lines over 80 characters", type=str)
	
	#parser.add_argument("-hello", "--test", type=testArgs1,help="Check lines over 80 characters")
	
	
	#print(args.test)
	#if(args.line-check):
	#	print("FUCK YOU")
	#parser.add_argument('--check', dest=
	
	
	#fileName = str(input("Enter the file name..ex 'bintree.cpp'(w/o Quotes):")) 
	#print("You gave me the filename: %s" % fileName)
	#checkLinesGreaterThan("bintree.cpp",80)
	#sanitize("bintree.cpp")

if __name__ == "__main__":
	#fileName = str(input("Enter the file name..ex 'bintree.cpp'(w/o Quotes):")) 
	#print("You gave me the filename: %s" % fileName)
	#checkLinesGreaterThan("bintree.cpp",80)
	#sanitize("bintree.cpp")

	
	main()
