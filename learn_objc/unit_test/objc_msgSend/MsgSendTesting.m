//
//  MsgSend.m
//  MacUnitTesting
//
//  Created by Felix on 9/8/17.
//  Copyright © 2017 Felix. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <objc/runtime.h>
#import <objc/objc.h>
#import <objc/message.h>
#import "Human.h"

#pragma clang diagnostic pop

//MARK: - Test

@interface MsgSendTesting : XCTestCase

@property (nonatomic, assign) NSUInteger times;

@end

@implementation MsgSendTesting

- (void)setUp {
    [super setUp];
    self.times = 1000 * 1000;
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
    XCTAssertTrue([[instance say:@"Hello"] containsString:@"Bark"]);
}

- (void)testDynamicForwardingInvocation{
    HumanForwardInvocation *instance = [[HumanForwardInvocation alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] containsString:@"Meow"]);
}

- (void)testMethodInvoke{
    
    Human *instance = [[Human alloc] init];
    Method method = class_getInstanceMethod([instance class], @selector(say:));
    
    uint64_t start = mach_absolute_time();
    
    NSString * result1 = ((NSString*(*)(id, Method, NSString*))method_invoke)(instance, method, @"Hello");
    NSLog(@"invoke = %llul", mach_absolute_time() - start);
    XCTAssertTrue([result1 isEqualToString:@"Hello"]);
    
    [self measureBlock:^{
        for (int i = 0; i < self.times; i++) {
            NSString *result2 __attribute__((unused)) = ((NSString*(*)(id, Method, NSString*))method_invoke)(instance, method, @"Hello");
        }
    }];
}

- (void)testImpAndSel {
    Human *instance = [[Human alloc] init];
    Method method = class_getInstanceMethod([instance class], @selector(say:));
    
    uint64_t start = mach_absolute_time();

    
    NSString *(*function)(id, SEL, NSString *) = (NSString *(*)(id, SEL, NSString *))method_getImplementation(method);
    SEL selecor = method_getName(method);
    NSString * result2 = function(instance, selecor, @"Hello");
    NSLog(@"iml&sel = %llul", mach_absolute_time() - start);
    
    XCTAssertTrue([result2 isEqualToString:@"Hello"]);
    [self measureBlock:^{
        for (int i = 0; i < self.times; i++) {
            NSString *(*function)(id, SEL, NSString *) = (NSString *(*)(id, SEL, NSString *))method_getImplementation(method);
            SEL selecor = method_getName(method);
            NSString *result2 __attribute__((unused)) = function(instance, selecor, @"Hello");
        }
    }];
}

@end
