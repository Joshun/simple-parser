#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define CHAR_TO_STRIP '='
#define TEXT_FILE "data.txt"

int check_char(char *str, int *pos);
int check_key(const char *src, const char *compare, const char strip);
int sep_key(char *src, char *split, char sep);
int retrieve_key_value(FILE *fp, char *key, char *value_store, int occurrence);

/* An example main program */
int main()
{
	FILE *test_fp = fopen(TEXT_FILE, "r");
	if( ! test_fp )
	{
		perror(TEXT_FILE);
		exit(1);
	}
	char value[1000];
	char value2[1000];
	retrieve_key_value(test_fp, "joshun", value, 1);
	printf("Value: %s\n", value);
	retrieve_key_value(test_fp, "noom", value2, 2);
	printf("Value: %s\n", value2);
	//printf("%d\n", check_key("hell=5", "hello", '='));
	fclose(test_fp);
	return 0;
}



int check_char(char *str, int *pos)
{
	char ch = str[*pos];
	
	switch( ch ) {
		case '#':
			while( ch != '\n' )
			{
				*pos = *pos + 1;
				ch = str[*pos];
				if( ch == '\0' || ch == EOF )
					return 0;
				printf("%c\n", str[*pos]);
			}
			return 1;
			break;
		case ' ':
			printf("Space\n");
			*pos = *pos + 1;
			return 1;
			break;
		case '\0':
		case EOF:
			printf("NULL or EOF\n");
			return 0;
			break;
		default:
			printf("OK\n");
			return 1;
	}
}

int check_key(const char *src, const char *compare, const char strip)
{
	printf("Source str %s\n", src);
	int src_size = strlen(src) + 1;
	char temp_buffer[src_size];
	
	int i;
	for(i=0; src[i] != '\0'; i++)
	{
		temp_buffer[i] = src[i];
		printf("Char %c\n", src[i]);
		if( temp_buffer[i] == strip )
		{
			temp_buffer[i] = '\0';
			break;
		}
	}
	temp_buffer[i+1] = '\0';
	printf("%s:%s\n", temp_buffer, compare);
	if( strcmp(temp_buffer, compare) == 0)
		return 1;
	else
		return 0;
}

int sep_key(char *src, char *split, char sep)
{
	int i, pos, found = 0;
	for(i=0; src[i] != '\0'; i++)
	{
		if( src[i] == sep )
		{
			pos = i;
			found = 1;
			break;
		}
	}
	if( found )
	{
		printf("Separator found\n");
		for(i=0; src[pos] != '\0'; i++)
		{
			check_char(src, &pos);
			pos++;
			split[i] = src[pos];
		}
		split[i + 1] = '\0';
		return 1;
	}
	else
		return 0;
}

int retrieve_key_value(FILE *fp, char *key, char *value_store, int occurrence)
{

	char buffer[BUFFER_SIZE] = { 0 };
	char buffer2[BUFFER_SIZE] = { 0 };
	int count = 0;
	int position = 0;
	int base = 0;

	fseek(fp, 0, SEEK_SET);
	
	while( fgets(buffer, sizeof(buffer), fp) ) {
		base = 0;
		position = 0;
		printf("Data read: %s\n", buffer);
		while( check_char(buffer, &position) ) {
			buffer2[base] = buffer[position];
			position++;
			base++;
		}
		buffer2[position + 1] = '\0';
		
		printf("Contents: %s\n", buffer2);
		if( check_key(buffer2, key, CHAR_TO_STRIP ) )
		{
			printf("Key %s found\n", key);
			count++;
			if( count == occurrence ) {
				sep_key(buffer2, value_store, CHAR_TO_STRIP);
				printf("Contents of key: %s\n", value_store);
				return 1;
			}
		}			
		
		memset(buffer2, '\0', sizeof(buffer));
		memset(buffer2, '\0', sizeof(buffer2));

	}
	
	return 0;
}
