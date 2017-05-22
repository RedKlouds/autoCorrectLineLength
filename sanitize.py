import argparse, glob, re, os


class Cleaner:
	_fileTypes = ('.php','.py','.js','.c','.java','.cpp')
		
	def __init__(self, usr_choice):
		"""
		Function Name: Default Constructor
		Description:
			-> Initializes the Cleaner object.
		PRECONDITION:
			-> None
		POSTCONDITION:
			-> Cleans the given files to limit 80 lines max
			per line.
		ASSUMPTIONS:
			-> None
		"""		
		#decide what the user wants to do
		#parse a single file or entire directory
		self._fileName = ""
		self._fileList = list()		
		self._checkUserInput(usr_choice)
		
	def _checkUserInput(self,usr_input):
		"""
		Function Name:
		Description:
			-> Method to check wether file input is valid extension
			/supported extension, this method is mainly used for
			-s args single file processing, multi processing has been
			handled
		PRECONDITION:
			->
		POSTCONDITION:
			->
		ASSUMPTIONS:
			-> None
		"""				
		if type(usr_input) == str:
			#if the input is a string check it for validility
			#our Regex  statment			
			matcher = re.compile('\.[^.]*$')
			extension = matcher.findall(usr_input)
		
			if len(extension) == 1:
				#we have valid extension
				#check if the extension is supported
				print('here')
				if extension[0] not in self._fileTypes:
					#not supported
					raise IOError("[+] File extension not supported")
			else:
				raise Exception("[+] Not a File")
			
		self._parseFiles(usr_input)

	def _parseFiles(self, userInput):
		"""
		Function Name: ParseFiles
		Description:
		    -> populate the files list array to prepare
			for processing.
		PRECONDITION:
		    -> User input must be a boolean or file(includes extension)
		POSTCONDITION:
		    -> sets the fileTypes array to all files in directory,
			or the indivudal file to parse.
		ASSUMPTIONS:
		    -> input needs to boolean or a string to a file.
		"""
		if type(userInput) == bool:
			#if -a args is true then start to gather all
			#files within the current directory specific to
			#supported file types
			for file in self._fileTypes:
				temp_file_name = "*%s" % file
				self._fileList.extend(glob.glob(temp_file_name))
		else:
			#append the file into the array
			self._fileList.append(userInput)
			
			
			
			
	def cleanUp(self):
		"""
		Function Name: 
		Description:
			-> for each file in the fileList, perform
			read, and write into clean folder operations
		PRECONDITION:
			->
		POSTCONDITION:
			->
		ASSUMPTIONS:
			-> None
		"""			
		if not os.path.exists("post_proccessed"):
			os.makedirs("post_proccessed")		
		for file in self._fileList:
			#call the parser to work on this particular file
			print("working on... %s" % file)
			#get the extension

			matcher = re.compile("(\w+)\.(.*)$")
			data = matcher.findall(file)
			fname = data[0][0]
			ext = data[0][1]
			#print(fname)
			#print("data : %s" % data)			
			#file_name = file.split('.')
			#ext = file_name[1]
			#file_name = file_name[0]
			
			ew_file = open("post_proccessed\\cleaned_%s.%s" % (fname, ext) , 'w')
			original_file = open(file)
			print(ext)
			
			
			
			
	def __str__(self):
		return self._user_choice
	
	
def sanitize(filename):
	f = open(filename).read().split('\n')
	newF = open("cleaned.cpp",'w')
	lineNumber = 0
	print("BEGIN")
	while(lineNumber != (len(f)-1)):
		#check if the current line number doesn't exceed the length of the parsed
		#file
		
		#for each parsed line check wether the length of that line is greater than 80
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


def checkLinesGreaterThan(fileName,lineLimit):
	"""
	Function Name:
	Description:
		->
	PRECONDITION:
		->
	POSTCONDITION:
		->
	ASSUMPTIONS:
		-> None
	"""			
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


if __name__ == "__main__":

	parser = argparse.ArgumentParser()

	parser.add_argument("-a","--all", help = "clean all files in current directory", action="store_true")
	parser.add_argument('-s',"--seperateFile", help= '[file] to clean seperate file')
	user_choice = False
	args = parser.parse_args()
	
	#all is where the item is saved, text
	if args.all:
		print("clean all files selected")
		user_choice = args.all
	elif args.seperateFile:
		print("clean seperate file: %s" %args.seperateFile)
		user_choice = args.seperateFile
	x = Cleaner(user_choice)
	x.cleanUp()


	print("Startting")