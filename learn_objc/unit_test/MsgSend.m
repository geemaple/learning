//
//  MsgSend.m
//  MacUnitTesting
//
//  Created by dean on 9/8/17.
//  Copyright © 2017 dean. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <objc/runtime.h>
#import <objc/objc.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincomplete-implementation"

//MARK: -

NSString * say(id self, SEL selector, NSString *msg){
    return [NSString stringWithFormat:@"%@", msg];
}

@interface HumanAddMethod: NSObject
- (NSString *)say:(NSString *)content;
@end

@implementation HumanAddMethod
- (instancetype)init{
    if(self = [super init]){
        const char *types = [[NSString stringWithFormat:@"%s%s%s%s", @encode(NSString *), @encode(id), @encode(SEL), @encode(NSString *)] cStringUsingEncoding:NSUTF8StringEncoding];
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

//MARK: -

@interface HumanFakeResolve: NSObject
- (NSString *)say:(NSString *)content;
@end

@implementation HumanFakeResolve
+ (BOOL)resolveInstanceMethod:(SEL)sel{
    if (sel == @selector(say:)) {
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}
@end

//MARK: -
@interface HumanResolve: NSObject
- (NSString *)say:(NSString *)content;
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

//MARK: -

@interface Dog : NSObject
- (NSString *)say: (NSString *)content;
@end

@implementation Dog

- (NSString *)say: (NSString *)content {
    return @"Bark";
}

@end

@interface HumanForwardTarget: NSObject{
    Dog *_surrogate;
}
- (NSString *)say:(NSString *)content;
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

//MARK: -

@interface Cat : NSObject
- (NSString *)say: (NSString *)content;
@end

@implementation Cat

- (NSString *)say: (NSString *)content {
    return @"Meow";
}

@end

@interface HumanForwardInvocation: NSObject{
    Cat *_surrogate;
}
- (NSString *)say:(NSString *)content;
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

#pragma clang diagnostic pop

//MARK: - Test

@interface MsgSend : XCTestCase

@end

@implementation MsgSend

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testDynamicAddFunctions{
    HumanAddMethod *instance = [[HumanAddMethod alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] isEqualToString:@"Hello"]);
}

- (void)testDynamicFakeResolve{
    HumanFakeResolve *instance = [[HumanFakeResolve alloc] init];
    XCTAssertThrowsSpecificNamed([instance doesNotRecognizeSelector:@selector(say:)], NSException, NSInvalidArgumentException);
    XCTAssertThrowsSpecificNamed([instance say:@"Hello"], NSException, NSInvalidArgumentException);
}

- (void)testDynamicResolveFunctions{
    HumanResolve *instance = [[HumanResolve alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] isEqualToString:@"Hello"]);
}

- (void)testDynamicForwardingTarge{
    HumanForwardTarget *instance = [[HumanForwardTarget alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] isEqualToString:@"Bark"]);
}

- (void)testDynamicForwardingInvocation{
    HumanForwardInvocation *instance = [[HumanForwardInvocation alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] isEqualToString:@"Meow"]);
}

@end
