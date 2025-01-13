//
//  ExistingMultiFileClass.m
//  ObjcWarmUps
//
//  Created by Felix on 9/9/17.
//  Copyright © 2017 Felix. All rights reserved.
//

#import "ExistingMultiFileClass.h"


@interface ExistingMultiFileClass()

//这是一个Extension
@property(nonatomic, assign)BOOL sick;

@end

@implementation ExistingMultiFileClass
- (NSString *)sayHi{ return @"ExistingMultiFileClass sayhi";}
@end
