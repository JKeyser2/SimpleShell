/*
project: 01
author: Jackson Keyser
email: jkeyser2@umbc.edu
student id: NI25410
description: a simple linux shell designed to perform basic linux commands
*/






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "utils.h"
#include <stdbool.h>






#define INITIAL_MAX_COMMAND_LENGTH 100
#define INITIAL_MAX_TOKENS_AMOUNT 100
#define MAX_LINE_LENGTH 100




/*
In this project, you are going to implement a number of functions to
create a simple linux shell interface to perform basic linux commands
*/








// DEFINE THE FUNCTION PROTOTYPES
void user_prompt_loop();
char *get_user_command();
char **parse_command(char *userInput);
int get_cpu_information(char *filePath);
int get_amount_running_processes(char *filePath);
int get_uptime(char *filePath);
int get_status_information(int thePid);
int get_environment_variables(int thePid);
int get_performance_information(int thePid);
int execute_command(char **userArguments);
int write_to_history(char *userInput);
int read_from_history();
int return_last_exit_status();




int main(int argc, char **argv)
{
    /*
    Write the main function that checks the number of argument passed to ensure
    no command-line arguments are passed; if the number of argument is greater
    than 1 then exit the shell with a message to stderr and return value of 1
    otherwise call the user_prompt_loop() function to get user input repeatedly
    until the user enters the "exit" command.
    */


    // If shell was run with any arguments, display an error message
    if (argc > 1){
        fprintf(stderr, "Shell was run with other argument(s). Does not accept command line arguments.");
        return 1;
    }

    user_prompt_loop();
}








/*
user_prompt_loop():
Get the user input using a loop until the user exits, prompting the user for a command.
Gets command and sends it to a parser, then compares the first element to the two
different commands ("/proc", and "exit"). If it's none of the commands,
send it to the execute_command() function. If the user decides to exit, then exit 0 or exit
with the user given value.
*/




void user_prompt_loop()
{
    // initialize variables




    /*
    loop:
        1. prompt the user to type command by printing >>
        2. get the user input using get_user_command() function
        3. parse the user input using parse_command() function
        Example:
            user input: "ls -la"
            parsed output: ["ls", "-la", NULL]
        4. compare the first element of the parsed output to "/proc"and "exit"
        5. if the first element is "/proc" then you have the open the /proc file system
        to read from it
            i) concat the full command:
                Ex: user input >>/proc /process_id_no/status
                    concated output: /proc/process_id_no/status
            ii) read from the file line by line. you may user fopen() and getline() functions
            iii) display the following information according to the user input from /proc
                a) Get the cpu information if the input is /proc/cpuinfo
                - Cpu Mhz
                - Cache size
                - Cpu cores
                - Address sizes
                b) Get the number of currently running processes from /proc/loadavg
                c) Get how many seconds your box has been up, and how many seconds it has been idle from /proc/uptime
                d) Get the following information from /proc/process_id_no/status
                - the vm size of the virtual memory allocated the vbox
                - the most memory used vmpeak
                - the process state
                - the parent pid
                - the number of threads
                - number of voluntary context switches
                - number of involuntary context switches
                e) display the list of environment variables from /proc/process_id_no/environ
                f) display the performance information if the user input is /proc/process_id_no/sched
        6. if the first element is "exit" the use the exit() function to terminate the program
        7. otherwise pass the parsed command to execute_command() function
        8. free the allocated memory using the free() function
    */




    /*
    Functions you may need:
        get_user_command(), parse_command(), execute_command(), strcmp(), strcat(),
        strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(), atoi(), fgetc(),
        or any other useful functions
    */






   // When true, the Shell will stop prompting for more user information
    bool stopPrompting = false;


    // For storing exit status
    int exitStatusInt = -99;



    // Keeps prompting the user for new input
    while(stopPrompting == false){
        // Prompt user to type command
        printf(">> ");


	int dumbBoolean = false;

        // Gets the command from the user
        char *theCommand = get_user_command();
        
        

	// Creating a copy of the command for later use
	size_t theCommandLength = strlen(theCommand);
    	char* theCommand2 = malloc(theCommandLength + 1);
    
    	strcpy(theCommand2, theCommand);  


        //free(theCommand2);













        // If the user entered an empty line
        if (strlen(theCommand) == 0){
            // Deallocate memory
            //free(theCommand);
            continue;
        }




        // Parsed data
        char **tokens = parse_command(theCommand);


        // Deallocate memory
        //free(theCommand);
        //printf("%s", tokens[0]);


        // Printing the tokens
        //for (int i = 0; i < sizeof(tokens); i++) {
            //printf("%s ", tokens[i]);
        //}




        // If the first element is "/proc"
        if(strcmp(tokens[0], "/proc") == 0){
         
            //exit(0);




            // Allocates memory for the user command
            char *combinedString = (char *)malloc(INITIAL_MAX_COMMAND_LENGTH * sizeof(char));






            // Copy the first token to the combined string
            strcpy(combinedString, tokens[0]);
         
         
            //exit(0);




            // Check the length of the combined string
            size_t currentLength = strlen(combinedString);




            // If enough space is allocated
            if(currentLength + strlen(tokens[1]) < INITIAL_MAX_COMMAND_LENGTH){
                // Concatenate the second token to the combined string
                strcat(combinedString, tokens[1]);
            // If not enough space allocated
            }else{
                // Find out exactly how much space needs to be allocated
                size_t newLength = currentLength + strlen(tokens[1]) + 1;
                // Allocate more space
                combinedString = (char *)realloc(combinedString, newLength * sizeof(char));






                // Concatenate the second token to the combined string
                strcat(combinedString, tokens[1]);
            }








        //exit(0);
     
     
        // This dumb "for" loop wants to access 1 index outside of where it...
        // ... should be, causing memory errors. My goofy fix
        // Still isn't perfect, but way less memory errors
        int coolCounter = 0;






    // Deallocate memory
    for (int i = 0; tokens[i] != NULL; ++i) {
    coolCounter++;
    }




    for(int i = 0; i < (coolCounter-1); i++){
    // FIX
    //free(tokens[i]);
    }



    // FIX
    //free(tokens);
         


            //printf("Combined string: %s\n", combinedString);




            // If this is the string, we need to get CPU information
            if(strcmp(combinedString, "/proc/cpuinfo") == 0){
                exitStatusInt = get_cpu_information(combinedString);
                }
            // If this is the string, we need to get the number of currently running processes
            else if(strcmp(combinedString, "/proc/loadavg") == 0){
                exitStatusInt = get_amount_running_processes(combinedString);
            }
            // If this is the string, we need to get the total uptime and idle time
            else if(strcmp(combinedString, "/proc/uptime") == 0){
                exitStatusInt = get_uptime(combinedString);
            }
            // If the sixth index of the string is a number, we are working with a process id number
            else if(combinedString[6] == '0' || combinedString[6] == '1' || combinedString[6] == '2' || combinedString[6] == '3' || combinedString[6] == '4' || combinedString[6] == '5' || combinedString[6] == '6' || combinedString[6] == '7' || combinedString[6] == '8' || combinedString[6] == '9'){
                int currentIndex = 6;
                // For storing the process ID number
                char processIdNumberAsString[MAX_LINE_LENGTH];
                // For storing current index in the process ID number string
                int processIdNumberAsStringIndex = 0;




                // While there is still numbers in the process ID
                while(combinedString[currentIndex] != '/'){
                    //printf("%c\n", combinedString[currentIndex]);
                    // Add the number to the string
                    processIdNumberAsString[processIdNumberAsStringIndex] = combinedString[currentIndex];
                    // Increment index of both strings
                    currentIndex++;
                    processIdNumberAsStringIndex++;
                }




                // Convert process ID number from string to an integer
                int thePid = atoi(processIdNumberAsString);




                //printf("Process ID: %d\n", thePid);




                //pid_t pid = getpid();
                //int thePid = pid;


                // If we are looking for Status
                if(combinedString[currentIndex + 1] == 's' && combinedString[currentIndex + 2] == 't'){
                    exitStatusInt = get_status_information(thePid);
                // If we are looking for environment variables
                }else if(combinedString[currentIndex + 1] == 'e'){
                    exitStatusInt = get_environment_variables(thePid);
                // If we are looking for performance information
                }else if(combinedString[currentIndex + 1] == 's' && combinedString[currentIndex + 2] == 'c'){
                    exitStatusInt = get_performance_information(thePid);
                }
            }




            // Deallocate memory
            // FIX
            //free(combinedString);
         
            //exit(0);
     




        // If we are returning last exit status using echo
        }else if( (tokens[1] != NULL) && (strcmp(tokens[1], "$?") == 0) ){
            return_last_exit_status();
            dumbBoolean = true;
        // If we are returning last exit status without using echo
        }else if(strcmp(tokens[0], "$?") == 0 ){
            return_last_exit_status();  
            dumbBoolean = true;
        }else if(strcmp(tokens[0], "exit") == 0){
            // FIX
            //free(theCommand);
            int coolCounter = 0;
            // Deallocate memory
            for (int i = 0; tokens[i] != NULL; ++i) {
                coolCounter++;
            }
         
            for(int i = 0; i < (coolCounter-1); i++){
            // FIX
            //free(tokens[i]);
            }
            // FIX
            //free(tokens);
            // 0 means a successful exit
            
            
            // Gets exit status
            if(tokens[1] != NULL){
                //printf("1");
                char stringExitStatus[strlen(tokens[1]) + 3];
                strcpy(stringExitStatus, " (");
                strcat(stringExitStatus, tokens[1]);
                strcat(stringExitStatus, ")");


                // Put the command and the exit status together
                strcat(theCommand2, stringExitStatus);


                //printf("1");
                write_to_history(theCommand2);
   
            }else{
                //printf("2");
                char stringExitStatus[1 + 3];
                strcpy(stringExitStatus, " (");
                strcat(stringExitStatus, "0");
                strcat(stringExitStatus, ")");
     
                // Put the command and the exit status together
                strcat(theCommand2, stringExitStatus);
     
                //printf("2");
                write_to_history(theCommand2);
             
            }
         
        
            stopPrompting = true;
            exit(0);
        // If user wants to see their history
        }else if(strcmp(tokens[0], "history") == 0){
            read_from_history();
        // Otherwise, pass the parsed command to execute_command function
        }else{
	    for(int i = 0; tokens[i] != NULL; ++i){
	        FILE *dummy_file = tmpfile();
	    	char *coolString = unescape(tokens[i], dummy_file);
	   
	    	
	    	if(coolString == NULL){
	    	    
	    	    coolString = tokens[i];
	    	    
	    	    int lengthOfString = strlen(coolString);
	    	    
	    	    char *coolString2 = malloc(strlen(coolString));
	    	    
	    	    //char coolString2[] = "";
	    	    
	    	    int coolString2CurrIndex = 0;
	    	    
	    	    for(int i = 0; i < lengthOfString; i++){
	    	        //printf("\nEPIC\n");
	    	        if(isalpha(coolString[i])){
	    	            coolString2[coolString2CurrIndex] = coolString[i];
	    	            coolString2CurrIndex++;
	    	            //printf("COOLSTRING2 %s\n", coolString2);
	    	        }
	    	    }
	    	    coolString2[coolString2CurrIndex + 1] = '\0';
	    	    //printf("COOLSTRING2 %s\n", coolString2);
	    	    coolString = coolString2;
	    	}

	    	//printf("Unescape: %s\n", coolString);
	    	tokens[i] = coolString;
	    }







            // For printing out index and the token
            for (int i = 0; tokens[i] != NULL; i++) {
                //printf("Token %d: %s\n", i, tokens[i]);
            }

	    char **userArguments = tokens;

	    
	     // For storing amount of commands to execute
	    int amountCommands = 1;

	    // Loops through tokens
	    for(int i = 0; userArguments[i] != NULL; i++){
		// If there is an &&, increment amount of commands to execute
		if(strcmp(userArguments[i], "&&") == 0){
		    amountCommands++;
		}
	    }
	    
	    
	    // If there is more than 1 command to execute
	    if(amountCommands > 1){
		// 2D array for storing
		// Rows are the commands
		// Columns are the parts of each command
		char allCommands[amountCommands][10][100];
		
		// Fill in the 2D array with empty values
		for(int i = 0; i < amountCommands; i++){
		    for(int j = 0; j < 10; j++){
		        strcpy(allCommands[i][j], "");
		    }
		}
		
		int currentCommand = 0;
		int currentPart = 0;
		
		// Loops through tokens
		for(int i = 0; userArguments[i] != NULL; i++){
		    // If still on current command
		    if(strcmp(userArguments[i], "&&") != 0){
		        sprintf(allCommands[currentCommand][currentPart], userArguments[i]);
		        currentPart = currentPart + 1;
		    // If moving on to next command
		    }else{
		        currentCommand = currentCommand + 1;
		        currentPart = 0;
		    }
		}
		
		
		// Loops through commands
		for(int i = 0; i < amountCommands; i++){
		    int actualCommandSize = 0;
		    // For resizing the list to actual size
		    for(int j = 0; j < 10; j++){
		        // If not blank space, increment counter
		        if(strcmp(allCommands[i][j], "") != 0){
		            actualCommandSize = actualCommandSize + 1;
		        }
		    }
		    
		    //printf("%d\n", actualCommandSize);
		    
		    // For storing command in a list
		    //char *currRow[10];
		    char **currRow = malloc(actualCommandSize * sizeof(char*));
	            // For storing full command
		    for(int k = 0; k < actualCommandSize; k++){
		        currRow[k] = allCommands[i][k];
		    }
		    // Executes single command
		    exitStatusInt = execute_command(currRow);
		    free(currRow);
		    
		}
	    // If just 1 command to execute
	    }else{
	    exitStatusInt = execute_command(tokens);
	    }



            //execute_command(tokens);
            // For storing length of the string
            //int stringLength = 0;








            // Getting the length of each token, add to the total length
            //for(int i = 0; tokens[i] != NULL; i++){
                //stringLength = stringLength + strlen(tokens[i]);
                // Add a plus one for each space
                //stringLength = stringLength + 1;
            //}








            // Final token doesn't have a space after it (it is end of string)
            //stringLength = stringLength - 1;








            // Allocate memory for the string, +1 for the null terminator
            //char *concatenatedString = (char *)malloc(stringLength + 1);








            //concatenatedString[0] = '\0';








            // Loop through all of the tokens
            //for(int i = 0; tokens[i] != NULL; i++){
                // Add each token to string
                //strcat(concatenatedString, tokens[i]);
                // If not last token, add a space
                //if(tokens[i + 1] != NULL){
                    //strcat(concatenatedString, " ");
                //}
            //}








            //printf("FINAL: %s", concatenatedString);








            //execute_command(concatenatedString);
         
        }
        //COOL GUY HERE
        // Write the command to a file that contains the history
        if (strcmp(theCommand, "history") != 0 && dumbBoolean == false){
            // Determine max length of string version of integer
            int maxLengthInteger = snprintf(NULL, 0, "%d", exitStatusInt) + 4;
            // Allocate memory for string version of integer
            char *integerAsString = (char *)malloc(maxLengthInteger * sizeof(char));
            // Convert from integer to a string
            snprintf(integerAsString, maxLengthInteger, " (%d)", exitStatusInt);
        
            // Put the command and the exit status together
            strcat(theCommand2, integerAsString);
        
            
            free(integerAsString);

            write_to_history(theCommand2);
        }
         
    }




}
/*
get_user_command():
Take input of arbitrary size from the user and return to the user_prompt_loop()
*/




char* get_user_command()
{
    /*
    Functions you may need:
        malloc(), realloc(), getline(), fgetc(), or any other similar functions
    */




    // Starts the buffer at initial max length of 100
    size_t bufferSize = INITIAL_MAX_COMMAND_LENGTH;






    // Allocates memory for the user command
    char *theCommand = (char *)malloc(bufferSize * sizeof(char));






    // Reads in the user's input
    fgets(theCommand, INITIAL_MAX_COMMAND_LENGTH, stdin);




    // Dynamically resize buffer if needed








    // Gets the length of the command
    size_t lengthOfCommand = strlen(theCommand);






    //printf("%zu", lengthOfCommand);


    //printf("%s\n", theCommand);






    // While the last character is not a newline
    // AND
    // There is more input available from the input stream...
    // ... Keep increasing the buffer
    while(theCommand[lengthOfCommand - 1] != '\n' && !feof(stdin)){
        //printf("%s\n", theCommand);
        // Double the size of the buffer
        bufferSize = bufferSize * 2;






        // Allocate more space to the command
        theCommand = realloc(theCommand, bufferSize * sizeof(char));




        // Starting from where it cut off last time (buffer size too small)
        // Read in the rest of the command
        fgets(theCommand + lengthOfCommand, bufferSize - lengthOfCommand, stdin);




        // Obtain the new length of the command
        lengthOfCommand = strlen(theCommand);




    }




    //printf("%s\n", theCommand);




    // Remove newline character
    theCommand[strcspn(theCommand, "\n")] = '\0';






    return theCommand;
}








/*
parse_command():
Take command grabbed from the user and parse appropriately.
Example:
    user input: "ls -la"
    parsed output: ["ls", "-la", NULL]
Example:
    user input: "echo   hello                   world  "
    parsed output: ["echo", "hello", "world", NULL]
*/






char **parse_command(char *userInput)
{
    /*
    Functions you may need:
        malloc(), realloc(), free(), strlen(), first_unquoted_space(), unescape()
    */






    // For keeping track of how many tokens we currently have
    int currentTokenIndex = 0;
    // For keeping track of max amount of tokens we can currently store
    int maximumTokens = INITIAL_MAX_TOKENS_AMOUNT;






    // Allocate memory for the array of tokens
    char **tokens = (char **)malloc(maximumTokens * sizeof(char *));






    // Tokenize the string
    char *token = strtok(userInput, " ");






    // Keep tokenizing until no more tokens are left
    while (token != NULL) {
        tokens[currentTokenIndex++] = token;
        token = strtok(NULL, " ");






        // If we ran out of space for the tokens, we need to allocate more memory
        if(currentTokenIndex >= maximumTokens){
            //printf("COOL!");
            // Double the size of the array
            maximumTokens = maximumTokens * 2;
            // Reallocate more memory
            tokens = (char **)realloc(tokens, maximumTokens * sizeof(char *));
        }
    }




    // When finished, shrink the array to the exact size
    // Add a + 1 so we can have 1 "(null)"
    tokens = (char **)realloc(tokens, (currentTokenIndex + 1) * sizeof(char *));
   
    // Printing the tokens
    // printf("Tokens:\n");
    //for (int i = 0; i < currentTokenIndex + 1; i++) {
        //printf("%s", tokens[i]);
    //}




    return tokens;
   
}






int get_cpu_information(char *filePath){
    // Attempts to open the file
    FILE *theFile = fopen(filePath, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }






    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;








    // Variables to store CPU information
    //char cpuMhz[MAX_LINE_LENGTH];
    //char cacheSize[MAX_LINE_LENGTH];
    //char cpuCores[MAX_LINE_LENGTH];
    //char addressSizes[MAX_LINE_LENGTH];




    // Read the file line by line
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
        // If it's one of the lines we want information on, parse it
        //if (strncmp(currentLine, "cpu MHz", 7) == 0) {
            //sscanf(currentLine, "cpu MHz\t: %[^\n]", cpuMhz);
        //} else if (strncmp(currentLine, "cache size", 10) == 0) {
            //sscanf(currentLine, "cache size\t: %[^\n]", cacheSize);
        //} else if (strncmp(currentLine, "cpu cores", 9) == 0) {
            //sscanf(currentLine, "cpu cores\t: %[^\n]", cpuCores);
        //} //else if (strncmp(currentLine, "address sizes", 13) == 0) {
            //sscanf(currentLine, "address sizes\t: %[^\n]", addressSizes);
        //}
        printf("%s", currentLine);
    }






    //printf("cpu MHz: %s\n", cpuMhz);
    //printf("cache size: %s\n", cacheSize);
    //printf("cpu cores: %s\n", cpuCores);
    //printf("address sizes: %s\n", addressSizes);




    // Deallocate memory
    free(currentLine);




    // Close the file
    fclose(theFile);




    return 1;
}






int get_amount_running_processes(char *filePath){
    // Attempts to open the file
    FILE *theFile = fopen(filePath, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }






    // Stores the line currently being read
    char currentLine[MAX_LINE_LENGTH];






    // Stores the 1 line
    //char entireLine[MAX_LINE_LENGTH];






    // Read the file (there is only 1 line)
    while (fgets(currentLine, sizeof(currentLine), theFile) != NULL){
        // Copy that line over
        //strncpy(entireLine, currentLine, sizeof(entireLine));
        printf("%s", currentLine);
    }




    //printf("Entire Line: %s\n", entireLine);








    // There is 3 spaces before the number of currently running processes
    //int currentSpace = 0;
    //int currentIndex = 0;




    //char numberCurrentlyRunningProcesses[MAX_LINE_LENGTH];


    // For storing current index in string we are parsing to
    //int currentIndex2 = 0;




    // Loop through entire line until the third space is reached
    //while(entireLine[currentIndex] != '\0' && currentSpace != 3) {
        // If we found a space, increment
        //if(entireLine[currentIndex] == ' '){
            //currentSpace++;
        //}
        // If we are at the third space, the next character is the number of currently running processes
        //if(currentSpace == 3){
            //printf("NICE: %c\n", entireLine[currentIndex]);
            //printf("NICE: %c\n", entireLine[currentIndex+1]);
            //printf("NICE: %c\n", entireLine[currentIndex+2]);
            // While we have not reached a slash, keep parsing
            // Jump to the next character which is the first number
            //currentIndex = currentIndex + 1;
            // While there is more to parse
            //while(entireLine[currentIndex] != '/'){
                //numberCurrentlyRunningProcesses[currentIndex2] = entireLine[currentIndex];
                //currentIndex++;
                //currentIndex2++;
            //}
            // So we don't access the above "if" statement again
            //currentSpace++;
        //}
        //currentIndex++;
    //}






    // Add a null terminator at the end of the string
    //numberCurrentlyRunningProcesses[currentIndex2] = '\0';




    //printf("Number of currently running processes: %s\n", numberCurrentlyRunningProcesses);




    // Close the file
    fclose(theFile);




    return 1;






}




int get_uptime(char *filePath){
    // Attempts to open the file
    FILE *theFile = fopen(filePath, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }




    // Stores the line currently being read
    char currentLine[MAX_LINE_LENGTH];




    // Stores the 1 line
    char entireLine[MAX_LINE_LENGTH];






    // Read the file (there is only 1 line)
    while (fgets(currentLine, sizeof(currentLine), theFile) != NULL){
        // Copy that line over
        strncpy(entireLine, currentLine, sizeof(entireLine));
    }








    //printf("Entire Line: %s\n", entireLine);






    // Next, we are splitting the line into 2 strings at the space




    char *token;






    // Get the first token
    token = strtok(entireLine, " ");








    // Keeps track of the current token we are on
    int theCounter = 0;


    // Loop through tokens (there is only 2)
    while (token != NULL) {
        if(theCounter == 0){
            printf("Total up time: %s\n", token);
        }






        if(theCounter == 1){
            printf("Total idle time: %s\n", token);
        }
        token = strtok(NULL, " ");




        theCounter++;
    }






    // Close the file
    fclose(theFile);






    return 1;








}






int get_status_information(int thePid){
    char fileName[256];
    // Stores path
    snprintf(fileName, sizeof(fileName), "/proc/%d/status", thePid);




   // Attempts to open the file
    FILE *theFile = fopen(fileName, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }






    //char buffer[1024];








    //printf("STARTS HERE:\n");






    // Read and print each line until the end of file is reached
    //while (fgets(buffer, sizeof(buffer), theFile) != NULL) {
        //printf("%s\n", buffer); // Print the line
    //}








    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;






    // Variables to store Status information
    //char vmSize[MAX_LINE_LENGTH];
    //char vmPeak[MAX_LINE_LENGTH];
    //char processState[MAX_LINE_LENGTH];
    //char parentPid[MAX_LINE_LENGTH];
    //char numberOfThreads[MAX_LINE_LENGTH];
    //char numberOfVoluntarySwitches[MAX_LINE_LENGTH];
    //char numberOfInvoluntarySwitches[MAX_LINE_LENGTH];






    // Read the file line by line
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
        // If it's one of the lines we want information on, parse it
        //if (strncmp(currentLine, "VmSize", 6) == 0) {
            //sscanf(currentLine, "VmSize\t: %[^\n]", vmSize);
        //} else if (strncmp(currentLine, "VmPeak", 6) == 0) {
            //sscanf(currentLine, "VmPeak\t: %[^\n]", vmPeak);
        //} else if (strncmp(currentLine, "State", 5) == 0) {
            //sscanf(currentLine, "State\t: %[^\n]", processState);
        //} else if (strncmp(currentLine, "PPid", 4) == 0) {
            //sscanf(currentLine, "PPid\t: %[^\n]", parentPid);
        //} else if (strncmp(currentLine, "Threads", 7) == 0) {
            //sscanf(currentLine, "Threads\t: %[^\n]", numberOfThreads);
        //} else if (strncmp(currentLine, "voluntary_ctxt_switches", 23) == 0) {
            //sscanf(currentLine, "voluntary_ctxt_switches\t: %[^\n]", numberOfVoluntarySwitches);
        //} else if (strncmp(currentLine, "nonvoluntary_ctxt_switches", 26) == 0) {
            //sscanf(currentLine, "nonvoluntary_ctxt_switches\t: %[^\n]", numberOfInvoluntarySwitches);
        //}
        printf("%s", currentLine);
    }






    //printf("VmSize: %s\n", vmSize);
    //printf("VmPeak: %s\n", vmPeak);
    //printf("State: %s\n", processState);
    //printf("PPid: %s\n", parentPid);
    //printf("Threads: %s\n", numberOfThreads);
    //printf("voluntary_ctxt_switches: %s\n", numberOfVoluntarySwitches);
    //printf("nonvoluntary_ctxt_switches: %s\n", numberOfInvoluntarySwitches);








    // Deallocate memory
    free(currentLine);




    // Close the file
    fclose(theFile);






    return 1;
}








int get_environment_variables(int thePid){
    char fileName[256];
    // Stores path
    snprintf(fileName, sizeof(fileName), "/proc/%d/environ", thePid);




    // Attempts to open the file
    FILE *theFile = fopen(fileName, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }




    //printf("STARTS HERE:\n");






    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;






    // Read until end of file
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
        // For each line
        for (int i = 0; i < currentLineRead; ++i) {
            // Replace null characters with newline characters for printing
            if (currentLine[i] == '\0') {
                printf("\n");
            // If not a newline character, just print
            }else {
                printf("%c", currentLine[i]);
            }
        }
    }








    // Deallocate memory
    free(currentLine);






    // Close the file
    fclose(theFile);






    return 1;
}








int get_performance_information(int thePid){
    char fileName[256];
    // Stores the path
    snprintf(fileName, sizeof(fileName), "/proc/%d/sched", thePid);




    // Attempts to open the file
    FILE *theFile = fopen(fileName, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("Error opening file\n");
        return -1;
    }






    //printf("STARTS HERE:\n");








    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;








    // Read until end of file
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
        // For each line
        for (int i = 0; i < currentLineRead; ++i) {
            // Print 1 character at a time
            printf("%c", currentLine[i]);
        }
    }








    // Deallocate memory
    free(currentLine);






    // Close the file
    fclose(theFile);






    return 1;
}








/*
execute_command():
Execute the parsed command if the commands are neither /proc nor exit;
fork a process and execute the parsed command inside the child process
*/








int execute_command(char **userArguments)
{
    /*
    Functions you may need:
        fork(), execvp(), waitpid(), and any other useful function
    */
    
    // For storing exit status of a process
    int exitStatus = 0;

    // Allocate memory for storing the command
    // The command is the first argument
    char theCommand[strlen(userArguments[0]) + 1]; // Allocate enough memory
    strcpy(theCommand, userArguments[0]);

    
    // Go through all of the tokens
    for(int i = 0; userArguments[i] != NULL; i++){
        // If a token mentions the home directory
        if(userArguments[i][0] == '~'){
            // Store home directory
            char *homeDirectory = getenv("HOME");
            
            // For storing the rest of the path
            char *restOfPath;
            char buffer[100];
            int counter = 0;
            
            // Get the rest of the path
            for(size_t j = 1; j < strlen(userArguments[i]); j++){
                buffer[j-1] = userArguments[i][j];
                counter++;
            }
            
            // Assign a null-terminator
            buffer[counter] = '\0';
            restOfPath = buffer;
            
            // Combine both strings
            strcat(homeDirectory, restOfPath);
            
            //printf("WOW: %s\n", homeDirectory);
            
            userArguments[i] = homeDirectory;
        }
    }



    //printf("The Command: %s", theCommand);


    // If user wants to change directories
    if(strcmp(theCommand, "cd") == 0){
        // If they did not specify a path, this means they want to go to home directory
        if(userArguments[1] == NULL){
            // Store home directory
            const char *homeDirectory = getenv("HOME");
	    // If they successfully changed directories
	    if(chdir(homeDirectory) == 0){
	        printf("Directory changed!\n");
	        return 1;
	    // If they were not successful in changing directories
	    }else{
	        printf("Directory did not change!\n"); 
	        return -1;
	    }
        }

    	
    	// If they successfully changed directories
        if(chdir(userArguments[1]) == 0){
            printf("Directory changed!\n");
            return 1;
        // If they were not successful in changing directories
        }else{
            printf("Directory did not change!\n"); 
            return -1;
        }
    }


    // If user wants to remove a file
    if(strcmp(theCommand, "rm") == 0){
    	// If they successfully removed the file
        if(remove(userArguments[1]) == 0){
            printf("File removed!\n");
            return 1;
        // If they were not successful in removing the file
        }else{
            printf("File not removed!\n"); 
            return -1;
        }
    }
    
 



    // Fork a new process
    pid_t pid = fork();








    //printf("pid: %d", pid);




    // Fork failed
    if(pid == -1){
        printf("Fork failed!\n");
        exit(-1);
    }
    // Is a child process
    else if(pid == 0){








        // Execute the command. If successful, doesn't return








        // If execution failed
        if(execvp(theCommand, userArguments) == -1){
            printf("Execution Failed!\n");
            exit(-1);
        }
    // Is a parent process
    }else{
        // Parent process
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);








        if (WIFEXITED(status)) {
            // Child process exited normally
            //printf("Child process exited with status %d\n", WEXITSTATUS(status));
            exitStatus = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            // Child process terminated by a signal
            //printf("Child process terminated by signal %d\n", WTERMSIG(status));
            exitStatus = WEXITSTATUS(status);
        }
    }
    
    return exitStatus;
}




int write_to_history(char *userInput){
    // Get the home directory path
    const char *homeDirectory = getenv("HOME");




    // If home directory path cannot be established
    if(homeDirectory == NULL){
    printf("Could not get the path for the home directory!");
    return -1;
    }




    // Get the length of the hoke directory and the name of the file
    char filePath[strlen(homeDirectory) + strlen("/.421sh") + 1];
    // Construct the full file path
    sprintf(filePath, "%s/%s", homeDirectory, ".421sh");
   
    // Create a file pointer to the file
    FILE *theFile = fopen(filePath, "r");




    // If file cannot be opened
    if(theFile == NULL){
    	// Try to create it instead with a write
    	// Create a file pointer to the file
    	FILE *theFile = fopen(filePath, "w");
    }
    
    // If the file still can't opened
    if(theFile == NULL){
        //printf("Weird bug. History should work for rest of commands.\n");
        return -1;
        }
    


    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;








    // For storing how many lines are currently in the file
    int counter = 0;


    // Stores the last nine lines of history
    char historyList[9][MAX_LINE_LENGTH];



    // Read until end of file
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
        // Skip the first line, we are going to shift all of the history 1 up
        if(counter != 0){
            strcpy(historyList[counter-1], currentLine);
        }
        counter++;
    }
    


    free(currentLine);
    
    fclose(theFile);




    bool shiftUp = false;

    //char coolBuffer[256];
        //while(fgets(coolBuffer, sizeof(coolBuffer), theFile)!= NULL){
        //printf("%s", coolBuffer);
    //}
    

    // If there is already 10 lines, we are going to shift up
    if(counter == 10){
        shiftUp = true;
    }

    FILE *theFile2 = NULL;

    // If we are not shifting up, use append
    if(shiftUp == false){
       // Create a file pointer to the file
        theFile2 = fopen(filePath, "a");
    // If we are shifting up, use write as it will clear the file
    }else{
        theFile2 = fopen(filePath, "w");
    }






    // If file cannot be opened
    if(theFile2 == NULL){
        printf("Failed to open file!");
        return -1;
    }




    if(shiftUp == true){
        //printf("SHIFTING UP\n");
        for(int i = 0; i < 9; i++){
            fprintf(theFile2, "%s", historyList[i]);
        }
        // Write the new command to the file
        fprintf(theFile2, "%s\n", userInput);
    }else{
        // Write the new command to the file
        fprintf(theFile2, "%s\n", userInput);
    }






    fflush(theFile2);




    // Closes the file
    //fclose(theFile);




    return 1;
}








int read_from_history(){
    // Get the home directory path
    const char *homeDirectory = getenv("HOME");








    // If home directory path cannot be established
    if(homeDirectory == NULL){
    printf("Could not get the path for the home directory!");
    return -1;
    }




    //printf("HOME DIRECTORY: %s", homeDirectory);



    // Get the length of the home directory and the name of the file
    char filePath[strlen(homeDirectory) + strlen("/.421sh") + 1];
    // Construct the full file path
    sprintf(filePath, "%s/%s", homeDirectory, ".421sh");








    // Attempts to open the file
    FILE *theFile = fopen(filePath, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("File can't be opened");     
    }
    
    // If file cannot be opened
    if(theFile == NULL){
    	// Try to create it instead with a write
    	// Create a file pointer to the file
    	FILE *theFile = fopen(filePath, "w");
    }
    
    // If the file still can't opened
    if(theFile == NULL){
        //printf("Weird bug. History should work for rest of commands.\n");
        return -1;
        }


    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;










    int index = 1;




   



    printf("HISTORY: \n");
    // Read until end of file
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
    //printf("boo yuh");
    printf("%d. %s", index, currentLine);
    index++;
    }








    // Deallocate memory
    free(currentLine);






    // Close the file
    //fclose(theFile);








    return 1;
}


int return_last_exit_status(){
    // Get the home directory path
    const char *homeDirectory = getenv("HOME");








    // If home directory path cannot be established
    if(homeDirectory == NULL){
    printf("Could not get the path for the home directory!");
    return -1;
    }




    //printf("HOME DIRECTORY: %s", homeDirectory);



    // Get the length of the home directory and the name of the file
    char filePath[strlen(homeDirectory) + strlen("/.421sh") + 1];
    // Construct the full file path
    sprintf(filePath, "%s/%s", homeDirectory, ".421sh");








    // Attempts to open the file
    FILE *theFile = fopen(filePath, "r");
    // If file cannot be opened
    if (theFile == NULL) {
        printf("File can't be opened");     
    }
    
    // If file cannot be opened
    if(theFile == NULL){
    	// Try to create it instead with a write
    	// Create a file pointer to the file
    	FILE *theFile = fopen(filePath, "w");
    }
    
    // If the file still can't opened
    if(theFile == NULL){
        //printf("Weird bug. History should work for rest of commands.\n");
        return -1;
        }


    // Pointer to the current line
    char *currentLine = NULL;
    // For storing the size of the buffer of the current line
    size_t currentLineBuffer = 0;
    // For storing the size of the current line, or -1 if there is an error
    ssize_t currentLineRead = 0;









    // For storing the amount of lines in the file
    int amountLines = 0;
    int currIndex = 0;




    // For storing the line
    char *lineCopy = NULL;


    // Read until end of file
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1) {
    
    amountLines++;
    
    
    }
    
    // Reset the file pointer to the beginning of the file
    fseek(theFile, 0, SEEK_SET);
    
    
    // Read through file again until at last line
    while ((currentLineRead = getline(&currentLine, &currentLineBuffer, theFile)) != -1){
        currIndex++;
        
        // If at last line
        if(currIndex == (amountLines)){
            // For getting last line
    
    	    // Allocate memory for storing the line
            char *lineCopy = malloc(currentLineRead + 1); 
            
        
            // Copy the contents of the current line to the allocated memory
            strcpy(lineCopy, currentLine);
            
            
            // For holding substring
	    char theSubstring[5];


	    // Get the substring from the string
	    char *substringOfString = strchr(lineCopy, '(');

	    // Copying the subtring over
	    strcpy(theSubstring, substringOfString);

	    printf("%s\n",theSubstring);
	 
        }
    }
    
    


    // Deallocate memory
    free(currentLine);

    free(lineCopy);





    // Close the file
    //fclose(theFile);








    return 1;
}
