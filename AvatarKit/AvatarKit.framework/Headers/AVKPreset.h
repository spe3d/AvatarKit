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


/**
 The type of a block to run when the preview image is finish to download.
 
 @see `-[AVKPreset observeDownloadedPreviewImage:]`
 */
typedef void(^AVKImageDownloadedBlock)(AVKPreset * _Nonnull preset, NSError * _Nullable error);


/**
 `AVKPreset` includes clothes or body language.
 You can use this object for your avatar to apply styles.
 */
@interface AVKPreset : NSObject

/**
 The type of preset.
 */
@property(nonatomic, assign, readonly) AVKPresetType type;

/**
 The preset can use for gender.
 */
@property(nonatomic, assign, readonly) AVKGender gender;

/**
 The name of preset.
 */
@property(nonnull, nonatomic, strong, readonly) NSString *name;

/**
 The preview image of preset.
 */
@property(nullable, nonatomic, strong, readonly) UIImage *previewImage;


/**
 Create a default preset.
 
 @param type
 The type of preset.
 
 @param gender
 The preset for gender.
 
 @return A default type of preset for gender.
 */
- (nonnull instancetype)initWithType:(AVKPresetType)type gender:(AVKGender)gender;

/**
 Create a default preset.
 You can set whether you need to download preview image at the same time.
 
 @param type
 The type of preset.
 
 @param gender
 The preset for gender.
 
 @param isNeeded
 Need to download preview image.
 
 @return A default type of preset for gender.
 */
- (nonnull instancetype)initWithType:(AVKPresetType)type gender:(AVKGender)gender downloadPreviewIfNeeded:(BOOL)isNeeded;

/**
 Get current usable the preset list.
 
 @param type
 The type of preset.
 
 @param gender
 The preset for gender.
 
 @return You can usable the preset list.
 
 */
+ (nonnull NSArray<AVKPreset *> *)getPresetsForType:(AVKPresetType)type gender:(AVKGender)gender NS_SWIFT_NAME(getPresets(for:gender:));

/**
 Get current usable the preset list.
 
 @param type
 The type of preset.
 
 @param gender
 The preset for gender.
 
 @return You can usable the preset list.
 
 */
+ (nonnull NSArray<AVKPreset *> *)getPresetsForTypes:(AVKPresetTypes)type gender:(AVKGender)gender NS_SWIFT_NAME(getPresets(for:gender:));

/**
 Adds an observe handler for downloads in this preset.
 
 The block has the following definition:
 
     typedef void(^AVKImageDownloadedBlock)(AVKPreset *preset, NSError *error);
 
 It receives the following parameters:
 
 - `AVKPreset`  \***preset**:        The preset for which this observe occurred.
 - `NSError`    \***error**:         An error object that indicates why the download failed, or nil if the download was successful.
 
 @param block
 A block which is called to process preview image.
 */
- (void)observeDownloadedPreviewImage:(nonnull AVKImageDownloadedBlock)block;

@end
