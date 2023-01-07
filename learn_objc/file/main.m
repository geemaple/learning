//
//  main.m
//  file
//
//  Created by Felix Ji on 1/7/23.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDownloadsDirectory, NSUserDomainMask, YES);
        NSString* documentsDirectory = [paths objectAtIndex:0];
        NSString* path1 = [documentsDirectory stringByAppendingPathComponent:@"testing1.txt"];
        NSString* path2 = [documentsDirectory stringByAppendingPathComponent:@"testing2.txt"];
        
        char *string = "hello world supposed to write to file 1, but write to file 2";
        
        int fd1 = open([path1 UTF8String], O_RDWR | O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
        // fd1 somehow closed
        close(fd1);
        
        int fd2 = open([path2 UTF8String], O_RDWR | O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
        
        // still wrtie to fd1
        ssize_t size = write(fd1, (const void *)string, strlen(string));
        
        close(fd2);
        NSLog(@"write bytes %zd", size);
        NSLog(@"%@", documentsDirectory);
    }
    return 0;
}
