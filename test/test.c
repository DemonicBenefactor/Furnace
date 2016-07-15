#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef windows
#define strdup _strdup 
#endif
//#include <SDL2/SDL.h>


// We begin with our linked list (for seperate chaining)
typedef struct _list_t_
{
    char *str;
    struct _list_t_ *next;
} list_t;

// Now we need a hash table structure
typedef struct _hash_table_t_
{
    int size; //size of the table
    list_t **table; //the table elements
} hash_table_t;

// Now we need a creation function
hash_table_t *create_hash_table( int size )
{
    hash_table_t *new_table;
    int i;

    if ( size < 1 ) return NULL; //invalid size for table
	
    // Attempt to allocate memory for the table structure
    if ((new_table = malloc( sizeof( hash_table_t ))) == NULL )
    {
	return NULL;
    }
    
    //Attempt to allocate memory for the table itself
    if ((new_table->table = malloc( sizeof( list_t * ) * size )) == NULL )
    {
	return NULL;
    }
    
    // Initialize the elemts of the table
    for ( i = 0; i < size; i++ )
    {
	new_table->table[i] = NULL;
    }
    
    // Set the size of the table
    new_table->size = size;
    
    return new_table;
}

// Our hash function
unsigned int hash( hash_table_t *hashtable, char *str )
{
    unsigned int hashval;
    hashval = 0; //we start our hash out at 0
    
    /*
    For eash character, we multiply the old hash
    by 31 and add the current character.  Remember
    that shifting a number left is equivalent to
    multiplying it by 2 raised to the number of 
    places shifted.  So we are in effect multiplying
    hashval by 32 and then subtracting hashval.
    Why do we do this?  Because shifting and subraction
    are more efficient operations than multiplication.
    */
    
    for ( ; *str != '\0'; str++ )
    {
	hashval = *str + ( hashval << 5 ) - hashval;
    }
    
    // We then return the hash value mod the hashtable size
    // // so that it will fit into the necessary range
    return hashval % hashtable->size;
}

// Lookup function
list_t *lookup_string( hash_table_t *hashtable, char *str )
{
    list_t *list;
    unsigned int hashval = hash( hashtable, str );
    
    /*
    Go to the correct list based on the hash value and see
    if str is in the list.  If it is, return return a pointer
    to the list element.  If it isn't, the item isn't in the 
    table, so return NULL.
    */
    for (list = hashtable->table[hashval]; list != NULL; list = list->next)
    {
	if ( strcmp( str, list->str ) == 0 )
	{
	    return list;
	}
	return NULL;
    }
    return NULL;
}

// Insert function
int add_string( hash_table_t *hashtable, char *str )
{
    list_t *new_list;
    list_t *current_list;
    unsigned int hashval = hash( hashtable, str );
    
    // Attempt to allocate memory for list
    if (( new_list = malloc( sizeof( list_t ))) == NULL )
    {
	return 1;
    }
    
    // Does the item already exist?
    current_list = lookup_string( hashtable, str );
    // The item already exists, don't insert it again.
    if ( current_list != NULL )
    {
	return 2;
    }
    
    // Insert it into the list
    new_list->str = strdup( str );
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    
    return 0;
}

// Delete table fucntion for freeing up memory
void free_table( hash_table_t *hashtable )
{
    int i;
    list_t *list, *temp;
    
    if ( hashtable == NULL ) return;
    
    // Free the memory for every item in the table
    for ( i = 0; i < hashtable->size; i++)
    {
	list = hashtable->table[i];
	while ( list != NULL )
	{
	    temp = list;
	    list = list->next;
	    free( temp->str );
	    free( temp );
	}
    }
    
    // Free the table itself
    free( hashtable->table );
    free( hashtable );
}

int main ( int argc, char* argv[] )
{
    hash_table_t *myHashTable;
    int sizeOfTable = 12;
    int stringAdded;
    char inputString[64];
    myHashTable =  create_hash_table( sizeOfTable );
    
    printf( "Please enter a word to add to the list: " );
    fgets( inputString, 64, stdin );
    stringAdded = add_string( myHashTable, inputString );
    
    switch (stringAdded)
    {
	case 1:
	    printf( "Couldn't Allocate memory for some reason\n" );
	    break;
	case 2:
	    printf( "This string is already in the list\n" );
	    break;
	case 0:
	    printf( "Success adding string: %s\n", inputString );
	    break;
	default:
	    printf( "unknown error\n" );
	    break;
    }
    
    free_table( myHashTable );
    
    return 0;
}

/***************************************************************
 * CHARACTER COUNTER
 * *************************************************************
#include <stdio.h>

int main (int argc, char* argv[])2
{
    int len = 0;
    
    printf("Enter a message: ");
    while (getchar() != '\n')
    {
	len++;
    }
    printf("Your message was %d character(s) long.\n", len);
	
    return 0;
}

***************************************************************/


/***************************************************************
* STRING REVERSE
* **************************************************************

#include <stdio.h>

#define XOR_SWAP(a,b) do\
{\
    a ^= b; \
    b ^= a; \
    a ^= b; \
} while (0)


size_t strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}

void inplace_reverse(char *str)
{
    if (str) // check that it's actaully a string
    {
	printf("The string is ");
	printf("%d", strlen(str));
	prin	XOR_SWAP(*str, *end);
		str++;
		end--;
	    }
	#undef XOR_SWAP
	}
    }
}

int main(int argc, char *argv[])
{
    char str[255];
    printf("\nEnter a string: ");
    gets(str);

    printf("\n\nNow we're going to reverse the string.\n");

    inplace_reverse(str);
    printf(str);
    printf("\n\n");

    return(0);

}tf(" characters long.\n");
	if (strlen(str) > 1) //make sure there's more than one character
	{
	    char *end = str + strlen(str) - 1;
	    while (str < end)
	    {
		XOR_SWAP(*str, *end);
		str++;
		end--;
	    }
	#undef XOR_SWAP
	}
    }
}

int main(int argc, char *argv[])
{
    char str[255];
    printf("\nEnter a string: ");
    gets(str);

    printf("\n\nNow we're going to reverse the string.\n");

    inplace_reverse(str);
    printf(str);
    printf("\n\n");

    return(0);

}
***************************************************************/
