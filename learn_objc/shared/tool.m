//
//  tool.m
//  learn_objc
//
//  Created by felix on 2025/1/13.
//

#include "tool.h"
#import <objc/runtime.h>
#import <objc/objc.h>

void printSuperClass(Class cls){
    
    NSString *title = [NSString stringWithFormat:@"💚 superclass: %s%s", class_getName(cls), class_isMetaClass(cls)? "[meta]": ""];
    NSUInteger length = title.length;
    NSString *padding = [@"" stringByPaddingToLength:length withString:@" " startingAtIndex:0];
    
    printf("%s", [title UTF8String]);
    Class cur = cls;
    while (class_getSuperclass(cur)) {
        Class super_cls = class_getSuperclass(cur);
        printf("%s => %s%s\n", [(cls == cur ? @"" : padding) UTF8String], class_getName(super_cls), class_isMetaClass(super_cls)?"[meta]": "");
        cur = super_cls;
    }
    printf("%s => nil \n", [padding UTF8String]);
}

void printIsaRelation(id obj) {
    Class cls = object_getClass(obj);
    NSString *title = @"💚 isa: ";
    NSUInteger length = [title length] + [[obj description] length];
    NSString *padding = [@"" stringByPaddingToLength:length withString:@" " startingAtIndex:0];
        
    printf("%s%s := %s%s\n", [title UTF8String], [[obj description] UTF8String], class_getName(cls), class_isMetaClass(cls) ? "[meta]" : "");
    
    while (object_getClass(cls)) {
        if (cls == object_getClass(cls)) {
            break;
        }
        cls = object_getClass(cls);
        printf("%s := %s%s\n", [padding UTF8String], class_getName(cls), class_isMetaClass(cls)? "[meta]": "");
    }
    
    printf("%s := ... \n", [padding UTF8String]); //  same as last
}
