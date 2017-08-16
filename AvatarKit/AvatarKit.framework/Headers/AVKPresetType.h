//
//  AVKPresetType.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/12.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, AVKPresetType) {
    AVKPresetTypeUnknown = 0,
    AVKPresetTypeSuit = 1,
    AVKPresetTypeAccessory,
    AVKPresetTypeHair,
    AVKPresetTypeMotion,
};

typedef NS_OPTIONS(NSInteger, AVKPresetTypes) {
    AVKPresetTypesSuit        = 1 << 0,
    AVKPresetTypesAccessory   = 1 << 1,
    AVKPresetTypesHair        = 1 << 2,
    AVKPresetTypesMotion      = 1 << 3,
};

NSString * _Nonnull NSStringFromAVKPresetType(AVKPresetType type);
