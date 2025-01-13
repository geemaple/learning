//
//  Feline.h
//  ObjcBasicsTesting
//
//  Created by Felix Ji on 12/30/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol Mutant <NSObject>

- (void)becomeLion;

@end

@interface Animal : NSObject

- (NSString *)say: (NSString *)content;
+ (NSString *)say: (NSString *)content;

@end

@interface Dog : Animal

@end

@interface Feline : Animal

@end

@interface Tiger : Feline

@property(nonatomic, copy) NSString *name;
@property(atomic, assign) BOOL isSick;

@end

@interface Cat : Feline
- (NSString *)say: (NSString *)content;
@end

@interface Tiger(Mogoal)
- (void)catCrawl;
@end

NS_ASSUME_NONNULL_END
