//
//  AVKPreset.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/12.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AvatarKit/AVKPresetType.h>
#import <AvatarKit/AVKGender.h>

@class AVKPreset;

typedef void(^AVKImageDownloadedBlock)(AVKPreset * _Nonnull preset, NSError * _Nullable error);


@interface AVKPreset : NSObject

@property(nonatomic, assign, readonly) AVKPresetType type;
@property(nonatomic, assign, readonly) AVKGender gender;
@property(nonnull, nonatomic, strong, readonly) NSString *name;
@property(nullable, nonatomic, strong, readonly) UIImage *previewImage;

- (nonnull instancetype)initWithType:(AVKPresetType)type gender:(AVKGender)gender;

- (nonnull instancetype)initWithType:(AVKPresetType)type gender:(AVKGender)gender downloadPreviewIfNeeded:(BOOL)isNeeded;

+ (nonnull NSArray<AVKPreset *> *)getPresetsForType:(AVKPresetType)type gender:(AVKGender)gender NS_SWIFT_NAME(getPresets(for:gender:));

+ (nonnull NSArray<AVKPreset *> *)getPresetsForTypes:(AVKPresetTypes)type gender:(AVKGender)gender NS_SWIFT_NAME(getPresets(for:gender:));

- (void)observeDownloadedPreviewImage:(nonnull AVKImageDownloadedBlock)block;

@end
