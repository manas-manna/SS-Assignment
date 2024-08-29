#include <unistd.h>
#include <stdio.h> 

int main() {
    char temp[1024];
    ssize_t bytes_read;//this line defines the number of bytes read from stdin_fileno
    //the 's' in ssize_t means signed int.size_t is portable and can handle any amount
    //large file.

    while ((bytes_read = read(STDIN_FILENO, temp,1024)) > 0) {
	  //This line says, "Try to read up to 1024 bytes from standard input
          // and store them in the temporary array temp.Then tell me how many bytes you actually 
          //read and store that in bytes_read."
        if (write(STDOUT_FILENO, temp, bytes_read) != bytes_read) {  //this line writing the data to stdout_fileno i.e, printing the output
        //if the number of bytes we entered is equal to no of bytes it printed then error may have  happened so handled them 
            perror("write"); 
            return 1; // Indicate an error
        }
    }

    if (bytes_read == -1) {
        perror("read");
        return 1; 
    }

    return 0; 
}
