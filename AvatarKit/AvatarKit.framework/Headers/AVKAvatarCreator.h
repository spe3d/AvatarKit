//
//  AVKAvatarCreator.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/9/15.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AvatarKit/AVKGender.h>
#import <AvatarKit/AVKAvatarController.h>


/**
 An `AVKAvatarCreator` object lets you create a scene node, including a avatar.
 An avatar creator is usually your first interaction with the scene node.
 */
@interface AVKAvatarCreator : NSObject

/**
 Use an image to create the landmarks for the face. And get the landmark information.
 
 @param faceImage
 The image must contain a face. This face to occupy 80% of the image.
 
 @param success
 The block to execute after the landmarks get. The block has no return value. The block will be passed an `NSArray` object containing `NSValue` objects which contain `CGPoint`.
 
 @param failure
 The block to execute failure. The block will be passed an `NSError` object if the landmarks could not be created.
 */
- (void)getLandmarksWithFaceImage:(nonnull UIImage *)faceImage successBlock:(void (^ _Nullable)(NSArray<NSValue *> * _Nonnull landmarks))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

/**
 Uploads image of face, that creates the avatar node.
 
 @param gender
 The gender of avatar.
 
 @param faceImage
 The image must contain a face. This face to occupy 80% of the image.
 
 @param success
 The block to execute after the avatar get. The block has no return value. The block will be passed an `AVKAvatarController` object.
 
 @param failure
 The block to execute failure. The block will be passed an `NSError` object if the avatar could not be created.
 */
- (void)createAvatarWithGender:(AVKGender)gender faceImage:(nonnull UIImage *)faceImage successBlock:(void (^ _Nullable)(AVKAvatarController * _Nonnull avatarController))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

/**
 Uploads image of face, that creates the avatar node.
 
 @param gender
 The gender of avatar.
 
 @param faceImage
 The image must contain a face. This face to occupy 80% of the image.
 
 @param fixLandmarks
 The landmarks for the face. You cannot pass any array. `fixLandmarks` must is based on `-getLandmarksWithFaceImage:successBlock:failureBlock:`.
 
 @param success
 The block to execute after the avatar get. The block has no return value. The block will be passed an `AVKAvatarController` object.
 
 @param failure
 The block to execute failure. The block will be passed an `NSError` object if the avatar could not be created.
 */
- (void)createAvatarWithGender:(AVKGender)gender faceImage:(nonnull UIImage *)faceImage fixLandmarks:(nullable NSArray<NSValue *> *)fixLandmarks successBlock:(void (^ _Nullable)(AVKAvatarController * _Nonnull avatarController))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

@end
