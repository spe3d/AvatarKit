//
//  AVKGender.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/11.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The gender of avatar.
 */
typedef NS_ENUM(NSUInteger, AVKGender) {
    /**
     The gender is male.
     */
    AVKGenderMale = 0,
    
    /**
     The gender is female.
     */
    AVKGenderFemale = 1,
};

/**
 Returns a string representation of a gender.
 
 @param gender
 The enum of gender.
 
 @return Returns a symbol string of the gender. The male is `M`. The female is `F`.
 */
NSString * _Nonnull NSStringFromAVKGender(AVKGender gender);
