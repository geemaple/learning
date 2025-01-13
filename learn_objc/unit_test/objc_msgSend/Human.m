//
//  Human.m
//  learn_objc
//
//  Created by felix on 2025/1/13.
//

#import "Human.h"
#import <objc/runtime.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincomplete-implementation"

//MARK: -

NSString * say(id self, SEL selector, NSString *msg){
    return [NSString stringWithFormat:@"%@", msg];
}

@implementation HumanAddMethod
- (instancetype)init{
    if(self = [super init]){
        const char *types = [[NSString stringWithFormat:@"%s%s%s%s", @encode(NSString *), @encode(id), @encode(SEL), @encode(NSString *)] UTF8String];
        NSMethodSignature *sig = [NSMethodSignature signatureWithObjCTypes:types];
        NSLog(@"💚 types=%s args= %lu rlength= %s rtype=%lu isOneway=%@", types, (unsigned long)sig.numberOfArguments, sig.methodReturnType, (unsigned long)sig.methodReturnLength, sig.isOneway ? @"YES": @"NO");
        
        for (int i = 0; i < sig.numberOfArguments; i++) {
            NSLog(@"    - %d arg type = %s", i, [sig getArgumentTypeAtIndex:i]);
        }
        
        class_addMethod([self class], @selector(say:), (IMP)say, types);
    }
    return self;
}
@end

@implementation HumanFakeResolve
+ (BOOL)resolveInstanceMethod:(SEL)sel{
    if (sel == @selector(say:)) {
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}
@end

@implementation HumanResolve
+ (BOOL)resolveInstanceMethod:(SEL)sel{
    if (sel == @selector(say:)) {
        const char *types = [[NSString stringWithFormat:@"%s%s%s%s", @encode(NSString *), @encode(id), @encode(SEL), @encode(NSString *)] cStringUsingEncoding:NSUTF8StringEncoding];
        class_addMethod([self class], sel, (IMP)say, types);
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}
@end

@implementation HumanForwardTarget

- (instancetype)init {
    if (self) {
        _surrogate = [[Dog alloc] init];
    }
    return self;
}

+ (BOOL)resolveInstanceMethod:(SEL)sel{
    NSLog(@"💚 1. resolveInstanceMethod called %@", NSStringFromSelector(sel));
    return [super resolveInstanceMethod:sel];
}

- (id)forwardingTargetForSelector:(SEL)aSelector{
    return _surrogate;
}

@end


@implementation HumanForwardInvocation

- (instancetype)init {
    if (self) {
        _surrogate = [[Cat alloc] init];
    }
    return self;
}

+ (BOOL)resolveInstanceMethod:(SEL)sel{
    NSLog(@"💚 1. resolveInstanceMethod called %@", NSStringFromSelector(sel));
    return [super resolveInstanceMethod:sel];
}

- (id)forwardingTargetForSelector:(SEL)aSelector{
    NSLog(@"💚 2. forwardingTargetForSelector called %@", NSStringFromSelector(aSelector));
    return [super forwardingTargetForSelector:aSelector];
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector{
    if ([_surrogate respondsToSelector:aSelector]) {
        return [_surrogate methodSignatureForSelector:aSelector];
    } else {
        return [super methodSignatureForSelector:aSelector];
    }
}

- (void)forwardInvocation:(NSInvocation *)anInvocation{
    if ([_surrogate respondsToSelector: [anInvocation selector]]){
        [anInvocation invokeWithTarget:_surrogate];
    }
    else{
        [super forwardInvocation:anInvocation];
    }
}
@end
