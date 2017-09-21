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

@interface AVKAvatarCreator : NSObject


/*!
 @method getLandmarksWithFaceImage:successBlock:failureBlock:
 
 @discussion
 Use an image to create the landmarks for the face. And get the landmark information.
 
 @param faceImage
 The image must contain a face. This face to occupy 80% of the image.
 
 @param success
 The block to execute after the landmarks get. The block has no return value. The block will be passed an NSArray object containing NSValue objects which contain CGPoint.
 
 @param failure
 The block to execute failure. The block will be passed an NSError object if the landmarks could not be created.
 */
- (void)getLandmarksWithFaceImage:(nonnull UIImage *)faceImage successBlock:(void (^ _Nullable)(NSArray<NSValue *> * _Nonnull avatarController))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

//! Uploads image of face, that creates the avatar node.
- (void)createAvatarWithGender:(AVKGender)gender faceImage:(nonnull UIImage *)faceImage successBlock:(void (^ _Nullable)(AVKAvatarController * _Nonnull avatarController))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

- (void)createAvatarWithGender:(AVKGender)gender faceImage:(nonnull UIImage *)faceImage fixLandmarks:(nullable NSArray<NSValue *> *)fixLandmarks successBlock:(void (^ _Nullable)(AVKAvatarController * _Nonnull avatarController))success failureBlock:(void (^ _Nullable)(NSError * _Nonnull error))failure;

@end
