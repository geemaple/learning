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
#import "Human.h"

#pragma clang diagnostic pop

//MARK: - Test

@interface MsgSendTesting : XCTestCase

@end

@implementation MsgSendTesting

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
    XCTAssertTrue([[instance say:@"Hello"] containsString:@"Bark"]);
}

- (void)testDynamicForwardingInvocation{
    HumanForwardInvocation *instance = [[HumanForwardInvocation alloc] init];
    XCTAssertTrue([[instance say:@"Hello"] containsString:@"Meow"]);
}

@end
