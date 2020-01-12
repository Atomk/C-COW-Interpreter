// TODO: allow reading source code from a file
// and solve all to-dos...
// Should also get rid of global variables since apparently they are evil

#include <stdio.h>  // Used for printf()
#include <stdlib.h> // Used for exit()


/***********************
        GLOBALS
***********************/


#define TRUE 1
#define FALSE 0

#define MEMORY_SIZE 100     // Must be greater than 0
#define COMMAND_LENGTH 3

enum { INVALID_COMMAND=-1, moo=0, mOo, moO, mOO, Moo, MOo, MoO, MOO, OOO, MMM, OOM, oom };

short memoryBlocksArray[MEMORY_SIZE];
short currentBlockIndex = MEMORY_SIZE / 2;

// Register, necessary for instruction MMM
short reg = 0;
short isRegisterInitialized = FALSE;

#define MAX_NUMBER_OF_INSTRUCTIONS 100
short opcodesArray[MAX_NUMBER_OF_INSTRUCTIONS];
short *jumpTable[MAX_NUMBER_OF_INSTRUCTIONS];

// "quick exit" demo
char *sourceCode = "OOOMOomOO";
// This should print an error, because of unimplemented instruction
//char *sourceCode = "OOOMoOMoOMoOMoOMoOMoOMoOMoOMMMmoOMMMMMMmoOMMMMOOMOomOoMoOmoOmoomOoMMMmoOMMMMMMmoOMMMMOOMOomOoMoOmoOmoomOoMMMmoOMMMMMMmoOMMMMOOMOomOoMoOmoOmooOOOMoOMoOMoOMoOMoOMoOmOoMMMmoOmoOMMMMOOMOomOoMoOmoOmoomOoMoomOoMMMmoOMMMmOomOoMMMmoOmoOmoOMMMMOOMOomOoMoOmoOmoomOoMMMmoOMMMMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoomOoMMMmoOMMMMoOMoomOoMMMmoOMMMMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMoOMooMOoMOoMOoMoo";


/***********************
         FUNCTIONS
***********************/


// Returns true if the two command strings are equal
// C does not have built-in string comparison (it's in string.h)
// Assumes strings have the same length
short commandNamesEqual(char *a, char *b)
{
    int i=0;

    for(i = 0; i < COMMAND_LENGTH; i++)
    {
        if(a[i] != b[i])
            return FALSE;
    }

    return TRUE;
}

void exitWithError(char *command, char *message)
{
    printf("Error [%s]: %s\n", command, message);
    // TODO: should find a way to exit from main function, both for clarity and because this causes errors if there's an opened file
    exit(EXIT_FAILURE);
}

// Takes a command (instruction) name and returns its instruction code
// If the command does not exist, returns INVALID_COMMAND
short getCommandCode(char *commandName)
{
    if(commandNamesEqual(commandName, "moo")) { return moo; }
    else if(commandNamesEqual(commandName, "mOo")) { return mOo; }
    else if(commandNamesEqual(commandName, "moO")) { return moO; }
    else if(commandNamesEqual(commandName, "mOO")) { return mOO; }
    else if(commandNamesEqual(commandName, "Moo")) { return Moo; }
    else if(commandNamesEqual(commandName, "MOo")) { return MOo; }
    else if(commandNamesEqual(commandName, "MoO")) { return MoO; }
    else if(commandNamesEqual(commandName, "MOO")) { return MOO; }
    else if(commandNamesEqual(commandName, "OOO")) { return OOO; }
    else if(commandNamesEqual(commandName, "MMM")) { return MMM; }
    else if(commandNamesEqual(commandName, "OOM")) { return OOM; }
    else if(commandNamesEqual(commandName, "oom")) { return oom; }
    
    return INVALID_COMMAND;
}

// Executes the command with the given command code.
// Returns index of the next line of code to execute
short execCommand(short commandCode, short caller, short currentLOC)
{
    switch (commandCode)
    {
        case 0: // moo
        
            // This command is connected to the MOO command. When encountered during normal execution,
            // it searches the program code in reverse looking for a matching MOO command
            // and begins executing again starting from the found MOO command.
            // When searching, it skips the instruction that is immediately before it (see MOO).
            exitWithError("moo", "not implemented yet");
            break;

        case 1: // mOo

            // Moves current memory position back one block
            if(currentBlockIndex > 0) {
                currentBlockIndex--;
            } else {
                exitWithError("mOo", "not enough memory.");
            }
            break;

        case 2: // moO

            // Moves current memory position forward one block
            if(currentBlockIndex < MEMORY_SIZE - 1) {
                currentBlockIndex++;
            } else {
                exitWithError("moO", "not enough memory.");
            }
            break;

        case 3: // mOO
        
            // Execute value in current memory block as if it were an instruction.
            // The command executed is based on the instruction code value (see https://bigzaphod.github.io/COW/)
            // (for example, if the current memory block contains a 2, then the moO command is executed).
            // An invalid command exits the running program.
            // Cannot call itself, as it would cause an infinite loop.
            if(memoryBlocksArray[currentBlockIndex] == commandCode) {
                exitWithError("mOO", "cannot call itself, it would cause an infinite loop.");
            }
            else {
                execCommand(memoryBlocksArray[currentBlockIndex], mOO, currentLOC);
            }
            break;

        case 4: // Moo

            // If current memory block has a 0 in it, read a single ASCII character from STDIN and store it in the current memory block.
            // If the current memory block is not 0, then print the ASCII character that corresponds to the value in the current memory block to STDOUT.
            // (I just call OOM for simplicity since it does exactly that)
            if(memoryBlocksArray[currentBlockIndex] == 0) {
                exitWithError("Moo", "not implemented yet");
            } else {
                if(memoryBlocksArray[currentBlockIndex] > 0 && memoryBlocksArray[currentBlockIndex] < 256) {
                    printf("%c", memoryBlocksArray[currentBlockIndex]);
                } else {
                    exitWithError("Moo", "this character cannot be printed to STDOUT.");
                }
            }
            break;

        case 5: // MOo

            // Decrement current block value by 1
            memoryBlocksArray[currentBlockIndex]--;
            break;

        case 6: // MoO

            // Increment current block value by 1
            memoryBlocksArray[currentBlockIndex]++;
            break;

        case 7: // MOO

            // If current memory block value is 0, skip next command and resume execution *after* the next matching moo command.
            // If current memory block value is not 0, then continue with next command.
            // Note that the fact that it skips the command immediately following it has interesting ramifications for where the matching moo command really is.
            // For example, the following will match the second and not the first moo: OOO MOO moo moo
            if(memoryBlocksArray[currentBlockIndex] == 0) {
                exitWithError("MOO", "not implemented yet");
                // skip next command and resume after next moo command
                // should give error if no moo found?
            }
            // else do nothing
            break;

        case 8: // OOO
        
            // Set current memory block value to zero
            memoryBlocksArray[currentBlockIndex] = 0;
            break;

        case 9: // MMM

            // If no current value in register, copy current memory block value.
            // If there is a value in the register, then paste that value into the current memory block and clear the register.
            if(!isRegisterInitialized) {
                reg = memoryBlocksArray[currentBlockIndex];
                isRegisterInitialized = TRUE;
            } else {
                memoryBlocksArray[currentBlockIndex] = reg;
                isRegisterInitialized = FALSE;
            }
            break;

        case 10: // OOM

            // Print value of current memory block to STDOUT as an integer
            printf("%d", memoryBlocksArray[currentBlockIndex]);
            break;

        case 11: // oom

            // Read an integer from STDIN and put it into the current memory block
            exitWithError("oom", "not implemented yet");
            break;

        default:

            if(caller == mOO) {
                /* TODO: from "mOO" description is not clear if the program should exit correctly or with an arror.
                Since there is no other way to exit, it shouldn't be an error I guess (only if the function is called because of mOO) */
                printf("[mOO]: quit program");
                exit(EXIT_SUCCESS);
            } else {
                exitWithError("execCommand()", "invalid command code.");
            }
    }

    return currentLOC + 1;
}


/***********************
         MAIN
***********************/


int main()
{
    printf("Number of memory blocks: %d\n", MEMORY_SIZE);
    printf("Index of current block: %d\n", currentBlockIndex);
    
    short commandCode = INVALID_COMMAND;
    short numberOfInstructions = 0;
    int i = 0;
    
    // Initialize memory to zeros
    for (i = 0; i < MEMORY_SIZE; i++)
    {
        memoryBlocksArray[i] = 0;
    }
    
    short suitableCharCount = 0;
    char commandName[COMMAND_LENGTH];

    // Read source code to find commands
    for(i = 0; sourceCode[i] != '\0'; i++)
    {
        // If the current character can be part of a command
        switch(sourceCode[i])
        {
            case 'm':
            case 'M':
            case 'o':
            case 'O':
                suitableCharCount++;
                break;
            default:
                // As per specification, any character that is not part of a command is ignored
                suitableCharCount = 0;
                continue;
        }

        // This works because every COW instruction is exactly 3 characters long
        if(suitableCharCount == COMMAND_LENGTH)
        {
            suitableCharCount = 0;

            // Turn the three consecutive suitable characters into a string
            commandName[0] = sourceCode[i-2];
            commandName[1] = sourceCode[i-1];
            commandName[2] = sourceCode[i];

            commandCode = getCommandCode(commandName);

            // If the found string is a valid command
            if(commandCode != INVALID_COMMAND)
            {
                printf("Found command: %s (%d)\n", commandName, commandCode);
                
                if(numberOfInstructions < MAX_NUMBER_OF_INSTRUCTIONS)
                {
                    opcodesArray[numberOfInstructions] = commandCode;
                    numberOfInstructions++;
                }
            }
            else
            {
                // If source code is "mmoo" -> "mmo" is not a valid command, but "moo" is.
                // This line allows to check the command validity again if the next character is suitable
                suitableCharCount--;
            }
        }
    }

    // EXECUTE PROGRAM

    i = 0;
    while(i < numberOfInstructions) {
        i = execCommand(opcodesArray[i], -1, i);
    }

    printf("Reached end of source code.\n");

    return 0;
}