#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define SUCCESS 1
/*
 * This is where the logic starts when you run the program, the main function. This program is used to get an estimate
 * on demo attempts in DOOM. It does this by the user giving the program percents in range 0-100. Each percent 
 * signifies the chance of beating a certain area or "part" of the run, an example could be beating the final area of a 
 * map with a strategy of a 50% survival rate, therefore the user would input 50 as one of the percents. Also checks
 * for special parameters too such as "-help" and "-avgtime hhmmss".
 * @author Brainfreezzzzz
 */
int main(int argc, char*argv[]){
	double product = 1;
	int numberOfParts = 0;
	double percent = 0;
	int time;
	unsigned int attempts;
	int averageTime = 0;
	int minutes = 0;
	int seconds = 0;
	int hours = 0;
	// Error checking to make sure program was ran with arguments
	if (argc == 1) {
		printf("%s", "Invalid number of arguments, if you need help, add the parameter '--help', or '-h'.\n");
		return ERROR;
	}
	// The main loop of the function that iterates over each argument the program was ran with
	for (int i = 1; i < argc; i++){
		// Makes sure the percents are in range
		if(atof(argv[i]) < 0.0f || atof(argv[i]) > 100.0f){
			printf("One of your percent was out of bounds: Percent #%d\n", i);
			return ERROR;	
		}
		// If a percent is in range, add it to the product of percents
		if(atof(argv[i]) > 0.0f && atof(argv[i]) <= 100.0f){
			percent = atof(argv[i]);
			product *= percent/100;
			numberOfParts += 1;
			continue;
		}
		// If the -avgtime extra parameter is used, harvest average time and set averageTime to 1.
		if (strcmp(argv[i],"-avgtime") == 0){
			if (averageTime == 1) {
				break;
			}
			if (i == argc - 1){
				break;
			}
			time = atoi(argv[i+1]);
			if (time == 0) {
				break;
			}
			seconds = time % 10;
			seconds += ((time % 100) / 10) * 10;
			minutes = time % 1000 / 10 / 10;
			minutes += time % 10000 / 10 / 10 / 10 * 10;	
			hours = time % 100000 / 10 / 10 / 10 / 10;	
			hours += time % 1000000 / 10 / 10 / 10 / 10 / 10 * 10;
			seconds += minutes * 60 + hours * 3600;
			i++;
			averageTime = 1;
		}	
		// If the -help, --help, or -h extra parameter is used, send the user this information
		if (strcmp(argv[i],"--help") == 0 || strcmp(argv[i],"-help") == 0 || strcmp(argv[i], "-h") == 0){
			printf("%s", "In order to run the program, you must use the following format.\n./destimator <Part 1 % of survival (0-100)> <Part 2 % of survial (0-100)> ...  <Part N % of survival (0-100)>\nExample: ./destimator 90 50 20 80 65 95\n");
			printf("You can also use the extra parameter -avgtime <hhmmss> to get an estimate amount of time for survival demo\nExample: ./destimator 90 50 20 80 65 95 -avgtime 123456 (123456 being 12 hours, 34 minutes, and 56 seconds)\nExample: ./destimator 90 50 20 80 65 95 -avgtime 354 (354 being 3 minutes, and 54 seconds)\n");
			return SUCCESS;
		}	
	}

	// Calculate and print survival percent and estimate attempts
	attempts = 1 / product;

	if (averageTime) {
		seconds = seconds * attempts;
		hours = seconds / 3600;
		minutes = seconds % 3600 / 60;
		seconds = seconds % 3600 % 60;
		printf("Estimate Survival Time: %d hours, %d minutes, and %d seconds\n", hours, minutes, seconds);

	}
	printf("Estimate Survival Percent: %0.2f\%%", product * 100);
	printf("\n");
	printf("Estimate Attempts: %d\n", attempts);
	return SUCCESS;
}
