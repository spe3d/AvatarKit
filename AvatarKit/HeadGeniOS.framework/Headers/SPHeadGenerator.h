//
//  SPHeadGenerator.h
//  HeadGeniOS
//
//  Created by DboyLiao on 28/03/2017.
//  Copyright © 2017 spe3d. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DataStructure.h"

typedef NS_ENUM(NSInteger, SPGender) {
    SPGenderMale = 0,
    SPGenderFemale = 1
};

@interface SPHeadGenerator : NSObject

-(nonnull instancetype)init;

- (nullable NSArray<NSValue *> *)generateLandmarks:(nonnull UIImage *)image;

- (nullable SPHeadModel *)generateHeadModel:(nonnull UIImage *)image
                                  landmarks:(nonnull NSArray<NSValue *> *)landmarks
                                     gender:(SPGender)gender;

-(nullable SPHeadModel *)generateHeadModel:(nonnull UIImage *)image
                                    gender:(SPGender)gender;

@end
