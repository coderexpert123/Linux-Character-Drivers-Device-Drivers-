#include <linux/module.h>      // Required for all kernel modules
#include <linux/kernel.h>      // Needed for KERN_INFO, printk, etc.
#include <linux/proc_fs.h>     // Provides functions for creating proc entries
#include <linux/init.h>        // Required for module init and exit macros
#include <linux/string.h>      // Needed for strlen function

MODULE_LICENSE("GPL");        // License type of the module
MODULE_AUTHOR("Nishant");     // Author of the module
MODULE_DESCRIPTION("A simple hello world module"); // Description of the module
MODULE_VERSION("0.01");       // Version of the module

// Pointer to the proc directory entry
static struct proc_dir_entry *custom_proc_module;

// Read function for the proc entry
static ssize_t nishant_read(struct file *file_pointer,
                             char __user *user_space_buffer,
                             size_t count,
                             loff_t *offset) {
    // Message to be read from the proc file
    char msg[] = "ACk\n";
    
    // Length of the message (excluding null terminator)
    size_t len = strlen(msg);
    
    // Print a message to the kernel log
    printk(KERN_INFO "Nishant reading from kernel space!\n");
    
    // Check if the offset is beyond the message length
    if (*offset >= len) {
        return 0; // Return 0 to indicate end of file
    }

    // Copy the message to user space
    if (copy_to_user(user_space_buffer, msg, len)) {
        return -EFAULT; // Return an error if copy_to_user fails
    }
 
    // Update the offset for the next read operation
    *offset += len; // Move the offset forward
    return len; // Return the number of bytes read
}

// Define the operations for the proc entry
struct proc_ops hello_proc_fops = {
    .proc_read = nishant_read, // Set the read function
};

// Module initialization function
static int __init custom_drv_init(void) {
    printk(KERN_INFO "Starting custom_drv_init init!\n");

    // Create a proc entry named "hello_proc"
    custom_proc_module = proc_create("hello_proc", 0, NULL, &hello_proc_fops);
    if (custom_proc_module == NULL) {
        // Log an error and return if creation fails
        printk(KERN_ERR "Failed to create /proc/hello_proc\n");
        return -ENOMEM; // Return memory allocation error
    }

    printk(KERN_INFO "custom_drv_init Exit!\n");
    return 0; // Return 0 to indicate successful initialization
}

// Module exit function
static void __exit custom_drv_exit(void) {
    printk(KERN_INFO "Starting custom_drv_exit Exit!\n");
    
    // Remove the proc entry created in init
    proc_remove(custom_proc_module);  

    printk(KERN_INFO "custom_drv_exit Exit!\n");
}

// Macros to specify the init and exit functions
module_init(custom_drv_init); // Define the init function
module_exit(custom_drv_exit);  // Define the exit function
