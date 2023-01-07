//
//  main.m
//  Category
//
//  Created by dean on 9/9/17.
//  Copyright © 2017 dean. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <objc/objc.h>

@protocol Catify <NSObject>

- (void)becomeACat;

@end

@interface PrisonCat : NSObject

@property(nonatomic, copy) NSString *name;
@property(nonatomic, readonly)BOOL sick;

- (void)meow;

@end


//Extension
@interface PrisonCat()

@property(nonatomic, readwrite)BOOL sick;

+ (void)meow;

@end

@implementation PrisonCat

- (void)meow{
    printf("instance meow\n");
}

+ (void)meow{
    printf("class meow\n");
}

- (NSString *)description {
    return @"Kitty";
}

@end

//Category
@interface PrisonCat(CatCategory)<Catify>

@property(nonatomic, readonly)BOOL useless;

- (void)helloThere;
+ (void)helloWorld;

@end

@implementation PrisonCat(CatCategory)

@dynamic useless;

- (void)helloThere{
    printf("nice there\n");
}

+ (void)helloWorld{
    printf("nice world\n");
}

- (void)becomeACat{
    printf("pretend to be a cat\n");
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        PrisonCat *kitty = [[PrisonCat alloc] init];
        
        [kitty meow];
        [[kitty class] meow];
        
        [kitty helloThere];
        [[kitty class] helloWorld];
    }
    return 0;
}
