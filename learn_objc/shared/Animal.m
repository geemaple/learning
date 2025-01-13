//
//  Feline.m
//  ObjcBasicsTesting
//
//  Created by Felix Ji on 12/30/20.
//

#import "Animal.h"
#import <objc/runtime.h>

@implementation Animal

- (NSString *)say: (NSString *)content {
    return [NSString stringWithFormat:@"[%@]~~~~", NSStringFromClass([self class])];
}

+ (NSString *)say: (NSString *)content {
    return [NSString stringWithFormat:@"[%@]~~~~", NSStringFromClass([self class])];
}

@end

@implementation Feline


@end

@implementation Dog

- (NSString *)say: (NSString *)content {
    return [NSString stringWithFormat:@"[%@]Bark", NSStringFromClass([self class])];
}

@end


@implementation Tiger

@end

@implementation Cat

- (Class)class {
    return [Feline class];
}

- (instancetype)init{
    if (self = [super init]) {
        NSLog(@"object_getClass self = %@", NSStringFromClass(object_getClass(self)));
        //如果Cat没有覆盖class方法，self和super结果是一样的
        NSLog(@"cls self = %@", NSStringFromClass([self class]));
        NSLog(@"cls super = %@", NSStringFromClass([super class]));
        NSLog(@"cls %@ super_cls\n", ([self class] == [super class] ? @"==" : @"!="));
    }
    return self;
}

- (NSString *)say: (NSString *)content {
    return [NSString stringWithFormat:@"[%@]Meow", NSStringFromClass([self class])];
}

+ (NSString *)say: (NSString *)content {
    return [NSString stringWithFormat:@"[%@]Meow", NSStringFromClass([self class])];
}

@end

@implementation Tiger(Mogoal)
- (void)catCrawl{
    printf("crawling x1 x2 x3 jump\n");
}
@end

