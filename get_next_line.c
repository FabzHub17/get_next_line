#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *stash;
    char *line;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // Read from file descriptor and append to stash
    stash = read_to_buffer(fd, stash);
    if(!stash)
        return (NULL);

    // Extract a complete line from stash
    line = extract_line(stash);

    // Update stash to keep remaining content for next call
    stash = update_buffer(stash);
    return (line);
}

char *read_to_buffer(int fd, char *stash)
{
    char *buffer;
    int bytes_read;

    // Allocate buffer for reading
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if(!buffer)
         return (NULL);

    bytes_read = 1; // Initialize to enter the loop
    while(bytes_read > 0)
    {
        
        bytes_read = read(fd, buffer, BUFFER_SIZE);  // Read chunk from file descriptor
        if(bytes_read == -1)
        {
            free(buffer);
            free(stash); // Free stash to prevent memory leak
            return (NULL);
        }
        buffer[bytes_read] = '\0';  // Null-terminate the buffer

        stash = join_and_free(stash, buffer); // Append buffer to stash
        if(!stash)
        {
            free(buffer);  // ******* free buffer or stash? *******
            return (NULL);
        }

        // Break if we found a newline
        if(ft_strchr(buffer, '\n'))
            break;

        // Also break if we've read less than BUFFER_SIZE bytes
        // (end of file reached)
        if (bytes_read < BUFFER_SIZE)
            break;
    }
    free(buffer);
    return (stash);
}

char *extract_line(char *stash)
{
    char *line;
    int i;
    
    // ******** A COSA SERVE QUESTO CONTROLLO? ********
    if (!stash || stash[0] == '\0')
        return (NULL);

    // Find end of line or end of string
    i = 0;
    while(stash[i] != '\n' && stash[i] != '\0')
        i++;

    // Allocate memory for the line (include newline if present)
    line = malloc((i + 2) * sizeof(char));  // 2 = 1 for line + 1 for null terminator???
    if(!line)
        return (NULL);

    // Copy data to the new line
    i = 0;
    while(stash[i] != '\n' && stash[i] != '\0')
    {
        line[i] = stash[i];
        i++;
    }

    // Include newline character if present
    if (stash[i] == '\n')
        line[i++] = '\n';

    line[i] = '\0';  // Null-terminate

    return (line);
}

char *update_buffer(char *stash)
{
    char *updated_stash;
    int i;
    int j;

    // ******** A COSA SERVE QUESTO CONTROLLO? ********
    if (!stash)
        return (NULL);

    // Find end of first line
    i = 0;
    while(stash[i] != '\n' && stash[i] != '\0')
        i++;

    // If no newline found, we've used all the buffer
    if(stash[i] == '\0')
    {
        free(stash);
        return (NULL);
    }
   
    i++; // Skip the newline character

    // Allocate memory for the remaining text
    updated_stash = malloc((ft_strlen(stash) - i + 1) * sizeof(char)); // DA VEDERE *******
    if(!updated_stash)
    {
        free(stash);
        return (NULL);
    }

    // Copy remaining text to the updated stash
    j = 0;
    while(stash[i] != '\0')
    {
        updated_stash[j] = stash[i];
        i++;
        j++;
    }
    updated_stash[j] = '\0';
    free(stash);
    return (updated_stash);
}
