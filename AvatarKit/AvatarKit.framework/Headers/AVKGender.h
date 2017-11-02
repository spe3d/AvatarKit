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
 
 公仔的性別。
 */
typedef NS_ENUM(NSUInteger, AVKGender) {
    /**
     The gender is male.
     
     此性別為男性。
     */
    AVKGenderMale = 0,
    
    /**
     The gender is female.
     
     此性別為女性。
     */
    AVKGenderFemale = 1,
};

/**
 Returns a string representation of a gender.
 
 回傳性別所代表的文字。
 
 @param gender
 The gender. 性別參數。
 
 @return Returns a symbol string of the gender. The male is `M`. The female is `F`.
 回傳性別所代表的文字。男性為`M`。女性為`F`。
 */
NSString * _Nonnull NSStringFromAVKGender(AVKGender gender);
