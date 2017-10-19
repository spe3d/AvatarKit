//
//  AVKPresetType.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/12.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The preset type.
 */
typedef NS_ENUM(NSUInteger, AVKPresetType) {
    /**
     The preset type is unknown.
     */
    AVKPresetTypeUnknown = 0,
    
    /**
     The preset type is suit.
     */
    AVKPresetTypeSuit = 1,
    
    /**
     The preset type is accessory.
     */
    AVKPresetTypeAccessory,
    
    /**
     The preset type is hair.
     */
    AVKPresetTypeHair,
    
    /**
     The preset type is motion.
     */
    AVKPresetTypeMotion,
};

/**
 The preset type. `AVKPresetTypes` can be multi-select.
 */
typedef NS_OPTIONS(NSInteger, AVKPresetTypes) {
    
    /**
     The preset type is suit.
     */
    AVKPresetTypesSuit        = 1 << 0,
    
    /**
     The preset type is accessory.
     */
    AVKPresetTypesAccessory   = 1 << 1,
    
    /**
     The preset type is hair.
     */
    AVKPresetTypesHair        = 1 << 2,
    
    /**
     The preset type is motion.
     */
    AVKPresetTypesMotion      = 1 << 3,
};

/**
 Returns a string representation of a preset type.
 
 @param type
 The enum of preset type.
 
 @return Returns a name of the preset type.
 */
NSString * _Nonnull NSStringFromAVKPresetType(AVKPresetType type);
