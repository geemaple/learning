//
//  Human.h
//  learn_objc
//
//  Created by felix on 2025/1/13.
//

#import "Animal.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincomplete-implementation"

@interface HumanAddMethod: NSObject
- (NSString *)say:(NSString *)content;
@end


@interface HumanFakeResolve: NSObject
- (NSString *)say:(NSString *)content;
@end


@interface HumanResolve: NSObject
- (NSString *)say:(NSString *)content;
@end

@interface HumanForwardTarget: NSObject{
    Dog *_surrogate;
}
- (NSString *)say:(NSString *)content;
@end

@interface HumanForwardInvocation: NSObject{
    Cat *_surrogate;
}
- (NSString *)say:(NSString *)content;
@end
