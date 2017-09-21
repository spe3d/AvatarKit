//
//  AVKAvatarController.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/7/12.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SceneKit.h>
#import <AvatarKit/AVKGender.h>
#import <AvatarKit/AVKPreset.h>

/**
 An `AVKAvatarController` class has a node of the avatar on a scene graph.
 You have to show the avatar, you need to add `sceneNode` in your scene.
 To modify style on the avatar, use methods of `AVKAvatarController` can immediately to update on the `sceneNode`.
 
 Save an Avatar
 
 AvatarKit provides to save an avatar to a file.
 `AVKAvatarController` class support the `NSSecureCoding` protocol.
 Use the `NSKeyedArchiver` class to serialize an avatar and all its contents, and the `NSKeyedUnarchiver` class to load an archived avatar.
 */
@interface AVKAvatarController : NSObject <NSSecureCoding>

@property(nonatomic, readonly) AVKGender avatarGender;
@property(nonatomic, readonly) NSInteger version;

//! Returns a Boolean value indicating whether the scene node wears preset.
@property(nonatomic, readonly) BOOL isWornPresets;

//! The node of the avatar on the scene graph.
@property(nonatomic, strong, readonly, nonnull) SCNNode *sceneNode;

@property(class, nonatomic, strong, readonly, nonnull) SCNNode *defaultCameraNode;


/**
 Create a default avatar.
 */
- (nonnull instancetype)initWithGenderOfDefaultAvatar:(AVKGender)gender;


- (void)observeAvatarHasWornPresets:(void (^ _Nonnull)(SCNNode * _Nonnull node))completed;

- (void)setSuit:(nonnull AVKPreset *)suit completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))block;

- (void)setMotion:(nonnull AVKPreset *)motion completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))block;

- (void)setHair:(nonnull AVKPreset *)hair completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))block;

- (void)setAccessory:(nullable AVKPreset *)accessory completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))block;

/**
 Changes facial at the avatar.
 We have more basic facial, the respective `weight` into the array where you can make the avatar show different facials.
 The `weight` range is 0-1.
 */
- (void)setFacialWithWeights:(nonnull NSArray<NSNumber *> *)weights;

@end
