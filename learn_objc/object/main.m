//
//  main.m
//  ClassObject
//
//  Created by Felix on 9/9/17.
//  Copyright © 2017 Felix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Animal.h"
#include "tool.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        printf("====start====");
        {
            Cat *cat = [[Cat alloc] init];
            Class cat_class = object_getClass(cat);
            NSLog(@"\nmain [cat class] %@ cat_class\n", ([cat class] == cat_class ? @"==" : @"!="));
            
            [cat say:@"hello"];
            [[cat class] say:@"hello"];
            
            printIsaRelation(cat);
            
            Class cls = object_getClass(cat);
            printSuperClass(cls);
            
            Class meta_cls = object_getClass(cls);
            printSuperClass(meta_cls);
        }
        printf("====end====");
    }
    return 0;
}
