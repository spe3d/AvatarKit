//
//  AVKGender.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/11.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, AVKGender) {
    AVKGenderMale = 0,
    AVKGenderFemale = 1,
};

NSString * _Nonnull NSStringFromAVKGender(AVKGender gender);
