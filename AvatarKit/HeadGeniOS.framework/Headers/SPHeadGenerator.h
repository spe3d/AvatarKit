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
    Male = 0,
    Female = 1
};

@interface SPHeadGenerator : NSObject

-(instancetype) init;
-(SPHeadModel *) generateHeadModel:(UIImage *) image
                            gender:(SPGender) gender;
@end
