/*****************************************************
 *
 *  CSCV352 - Exercise4_4.c
 *
 *  Student:  Francisco Figueroa
 *
******************************************************/
#include <stdio.h>
#include <string.h>


///////////////////////////////////////////////////////
//                CONSTANTS
///////////////////////////////////////////////////////

#define getName(var) #var

const char *headSections[5] = {"\tSource Port:\t\t",
							   "\tDestination Port: \t",
							   "\tSequence No:\t\t",
							   "\tAck No:\t\t\t",
							   "\tFlags:\t\t\t"};

#define CWR 128
#define ECE 64
#define URG 32
#define ACK 16
#define PSH 8
#define RST 4
#define SYN 2
#define FIN 1

const int flaArray[8] = {CWR, ECE, URG, ACK, PSH, RST, SYN, FIN};
const char *flaStrings[8] = {"CWR", "ECE", "URG", "ACK", "PSH", "RST", "SYN", "FIN"};


///////////////////////////////////////////////////////
//               typedefs and structures
//////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//               globalVariables
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//                FunctionPrototypes
///////////////////////////////////////////////////////
void DumpHex(const void* data, size_t size, int width);
int DisplayTCPSegment(unsigned char *pSegment, int segmentLen);



/*****************************************************
 *
 *  Function:  main()
 *
 *  Parameters:
 *
 *      argc - main parameter for argument count
 *      argv - main parameter for argument values
 *
******************************************************/
int main(int argc, char *argv[]) 
{
    unsigned char segmentBuffer[1500];
    int bytesRead;
	
    // Read the TCP segment from stdin
    bytesRead = fread(segmentBuffer, 1, 1500, stdin);

    // Uncomment this line to dump the packet to the console
    //DumpHex(segmentBuffer, bytesRead, 16);

    // ADD YOUR CALL TO DisplayTCPSegment() HERE
	DisplayTCPSegment(segmentBuffer, bytesRead);
	
    return 0;

}

/*******************************************************************
 * 
 *   DumpHex()
 * 
 *   Formatted output of raw data.
 * 
*******************************************************************/
void DumpHex(const void* data, size_t size, int width) 
{
	char ascii[17];
	size_t i, j;

	ascii[width] = '\0';
	for (i = 0; i < size; ++i) 
    {
        // Print the value
		printf("%02X ", ((unsigned char*)data)[i]);

        // save the ascii display value in the relative position
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') 
        {
			ascii[i % width] = ((unsigned char*)data)[i];
		} 
        else 
        {
			ascii[i % width] = '.';
		}


		if ((i+1) % (width / 2) == 0 || i+1 == size) 
        {
			printf(" ");
			if ((i+1) % width == 0) 
            {
				printf("|  %s \n", ascii);
			} 
            else if (i+1 == size) 
            {
				ascii[(i+1) % width] = '\0';
				if ((i+1) % width <= (width / 2)) 
                {
					printf(" ");
				}
				for (j = (i+1) % width; j < width; ++j) 
                {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

/*******************************************************************
 * 
 *   DisplayTCPSegment()
 * 
 *   pSegment - the pointer to the character array that holds the hexadecimal
 * values associated with the TCP header
 * 	 segmentLen - The length
 * 
*******************************************************************/
int DisplayTCPSegment(unsigned char *pSegment, int segmentLen)
{
	int section = 0;
	size_t i;
	int source = ((pSegment[0] << 8) | pSegment[1]);
	int dest = ((pSegment[2] << 8) | pSegment[3]);
	int seq =  ((pSegment[4] << 24) | (pSegment[5] << 16) | (pSegment[6] << 8) | (pSegment[7]));
	int ack =  ((pSegment[8] << 24) | (pSegment[9] << 16) | (pSegment[10] << 8) | (pSegment[11]));
	int flags = (pSegment[13]);

	int arr[5] = {source, dest, seq, ack, flags};
	printf("TCP Header Fields:\n");
	while (section <= 4)
	{
		printf("%s",headSections[section]);
		if (section == 2 || section == 3)
		{
			printf("%u\n",(unsigned)arr[section]);
		}
		else
		{
			printf("%d\n",arr[section]);
		}
		section++;
	}
	printf("\t ");
	for(i=0; i <= 7; i++)
	{
		if ((flags & flaArray[i]) != 0)
		{
			printf("%s ", flaStrings[i]);
		}
		continue;
	}
	printf("\n");
	return segmentLen;
}
