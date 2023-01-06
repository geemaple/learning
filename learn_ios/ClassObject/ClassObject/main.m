//
//  main.m
//  ClassObject
//
//  Created by dean on 9/9/17.
//  Copyright © 2017 dean. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <objc/objc.h>
#import "CatAnimal.h"

void printSuperClass(Class cls){
    printf("superclass: %s%s", class_getName(cls), class_isMetaClass(cls)?"[meta]": "");
    while (class_getSuperclass(cls)) {
        cls = class_getSuperclass(cls);        
        printf(" => %s%s", class_getName(cls), class_isMetaClass(cls)?"[meta]": "");
    }
    printf(" => nil \n");
}

void printIsaRelation(id obj) {
    Class cls = object_getClass(obj);
    printf("isa: %s := %s%s", [[obj description] UTF8String], class_getName(cls), class_isMetaClass(cls) ? "[meta]": "");
    while (object_getClass(cls)) {
        if (cls == object_getClass(cls)) {
            break;
        }
        cls = object_getClass(cls);
        printf(" := %s%s", class_getName(cls), class_isMetaClass(cls)? "[meta]": "");
    }
    
    printf(" := %s%s := ...\n", class_getName(cls), class_isMetaClass(cls)? "[meta]": "");
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        PrisonCat *kitty = [[PrisonCat alloc] init];
        Class cat_class = object_getClass(kitty);
        NSLog(@"\nmain [cat class] %@ cat_class\n", ([kitty class] == cat_class ? @"==" : @"!="));
        
        [kitty fullySick];
        [[kitty class] fullySick];
        
        printIsaRelation(kitty);
        
        Class cls = object_getClass(kitty);
        printSuperClass(cls);
        
        Class meta_cls = object_getClass(cls);
        printSuperClass(meta_cls);
    }
    return 0;
}
