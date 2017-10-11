//
//  AvatarKit.h
//  AvatarKit
//
//  Created by Hao Lee on 2017/6/30.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AvatarKit/AVKAvatarCreator.h>
#import <AvatarKit/AVKAvatarController.h>
#import <AvatarKit/AVKGender.h>
#import <AvatarKit/AVKPreset.h>
#import <AvatarKit/AVKPresetType.h>

@interface AvatarKit : NSObject

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//! Access the singleton AvatarKit instance.
@property(class, readonly, nonnull, strong) AvatarKit *sharedInstance NS_SWIFT_NAME(shared);
#endif

//! Project version string for AvatarKit.
@property(nonatomic, readonly, nonnull) NSString *version;

//! The AvatarKit API Key for this app
@property(nonatomic, strong, readonly, nullable) NSString *APIKey;

- (nonnull instancetype)init __unavailable;

/**
 The recommended way to install `AvatarKit` into your APP is to place a call to `+startWithAPIKey:` in your `-application:didFinishLaunchingWithOptions:` or `-applicationDidFinishLaunching:` method.
 
 @param apiKey The AvatarKit API Key for this app
 */
+ (void)startWithAPIKey:(nonnull NSString *)apiKey;

/**
 The recommended way to install `AvatarKit` into your APP is to place a call to `+startWithAPIKey:` in your `-application:didFinishLaunchingWithOptions:` or `-applicationDidFinishLaunching:` method.
 
 @param apiKey The AvatarKit API Key for this app
 @param betaMode The AvatarKit use beta version on server.
 */
+ (void)startWithAPIKey:(nonnull NSString *)apiKey onBetaServer:(BOOL)betaMode;

@end
