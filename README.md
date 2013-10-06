# A simple file parser / config file reader

## Interprets config files where the format is as follows:

    key1=value1
    key2=value2

## Multiple keys with the same name can be distinguished by specifying a different occurrence, e.g.:

    # Setup section 1
    mykey=value1
    #

    # Setup section 2
    mykey=value2
    #

## The main function to use is as follows:

    int retrieve_key_value(FILE *fp, char *key, char *value_store, int occurrence)

Where '*fp' is a file pointer of an already open file, 'key' is the key to search for and retrieve, 'value_store' is a
variable in which to store the retrieved value, and 'occurrence' is the numbered occurrence to retrieve. It returns 1 (TRUE)
on retrieving a key, and 0 (FALSE) on failing to do so.