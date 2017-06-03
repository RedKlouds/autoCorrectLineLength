import argparse, glob, re, os

#################################################################
#
# Program Description: This program takes all or a single file
#and looks for lines in which are greater than 80 characters long
#, which is then refactored to the next time, making a tidy
# no longer than 80 character per line source file.
#
# Nodes: this program only supports php py js c java c++ files so far
#
#
####################################################################
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
                self.MAX_LENGTH = 80
                
        def _checkUserInput(self,usr_input):
                """
                Function Name:
                Description:
                        -> Method to check wether file input is valid extension
                        /supported extension, this method is mainly used for
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
                                if extension[0] not in self._fileTypes:
                                        #not supported
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
                                #combine list
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

#
                        #get the data for block comment and single comment syntax
#


                        data = self.getCommentSyntax(ext)
                        #now check wether each line is:
                        # a single comment line
                        # or a multi comment block
                        with open(file) as originalFile:
                            for line in originalFile:
                                    
                                    
                                # get leading spaces
                                spaces = len(line) - len(line.lstrip())
                                #get length of block comment
                                #get length of single comment

#
                                #get the first charcter of single and block comment and compare
#


                                len_singleCom = len(data['singleL'])

                                len_BlockComSrt = len(data['blockStart'])
                                len_BlockComEnd = len(data['blockEnd'])
                                #print(line)
                                #print('firstChar : %s' % first_char)
                                #print('second block char: %s' % block_char)
#
                                #these lines exceed the maximum specified length
#

                                if len(line) > self.MAX_LENGTH:
                                        if first_char == data['singleL'] :
                                                new_file.write(edited)
                                        elif block_char == data['blockStart'] :
#
                                                #print('FOUND a COMMENT BLOCK \n%s\n' % line)
#

                                        #this is actual Code to indent         
##                                        else:
##                                                print(line)
                                else:
                                        #less than the MAX_LENGTH
                                  
                                        new_file.write(line)
                        new_file.close()
                       
                #creates and returns a commented block
                result_string = "%s" % startSyntax
                temp_line = line
                while len(temp_line) > self.MAX_LENGTH:
                        a = temp_line[:self.MAX_LENGTH-1]
                        temp_line = temp_line[self.MAX_LENGTH-1:]
                        result_string +="\n%s" % a
                if singleLine:
                        result_string += "%s%s\n" % (temp_line,startSyntax)
                else:
                        result_string +="\n%s" % temp_line
                result_string += "\n%s"% endSyntax
                return result_string
        
        
#
                #read the first opening block comment, until we meet out closing
#

                #check wether its a single line comment block
                #we already know the beginning syntax exist
                refined_text = line.replace(startSyntax, '')
                refined_text = refined_text.replace(endSyntax, '')
                if endSyntax in line:
                        #if its a single block comment break it into parts
#
                        #("%s \n %s\n %s " % (startSyntax, refined_text, endSyntax))
#

                else:
                        _line = line.rsplit('\n')

                       
                        edited = self.makeCommentBlock(line, startSyntax,'')
                        new_file.write(edited)
                        for line in original_file:
                                #organize the comment block
                                #until we encounter the closing/ending
                                #block comment character
                                if endSyntax in line:
                                        new_file.write(edited)
                                        new_file.write("\n%s"%endSyntax)
                                        break
                                if len(line) > self.MAX_LENGTH -1:
                                        
                                        new_file.write(edited)
                
        def getCommentSyntax(self, ext):
                """

                """
                syntax_store = \
                {'php':{
                        'singleL':'//',
                        'blockStart':'/*',
                        'blockEnd':'*/'
                        },
                 'py':{
                         'singleL':'#',
                         'blockStart':'"""',
                         'blockEnd':'"""'
                         },
                 'js':{
                         'singleL':'//',
                         'blockStart':'/*',
                         'blockEnd':'*/'
                         },
                 'cpp':{
                         'singleL':'//',
                         'blockStart':'/*',
                         'blockEnd':'*/'
                         },
                 'java':{
                         'singleL':'//',
                         'blockStart':'/*',
                         'blockEnd':'*/'
                         },
                 'c':{
                         'singleL':'//',
                         'blockStart':'/*',
                         'blockEnd':'*/'
                         }
                 }
                return syntax_store[ext]





if __name__ == "__main__":

        parser = argparse.ArgumentParser()

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
