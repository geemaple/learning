//
//  tool.h
//  learn_objc
//
//  Created by felix on 2025/1/13.
//

#import <Foundation/Foundation.h>

extern uintptr_t _objc_rootRetainCount(id obj); // 这是个私有API，作用是返回obj的引用计数。
extern void _objc_autoreleasePoolPrint(void); //这是个私有API, 作用是打印当前的自动释放池对象。

void printSuperClass(Class cls);
void printIsaRelation(id obj);
