def read_proc_file():
    # Open the proc file in read mode
    with open('/proc/hello_proc', 'r') as file:
        # Read the content of the file
        content = file.read()
        # Print the content to the console
        print(content)

if __name__ == "__main__":
    # Call the function to read from the proc file when the script is run
    read_proc_file()
