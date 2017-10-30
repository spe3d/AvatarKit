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


/**
 AvatarKit Base. Handles configuration and initialization of AvatarKit.
 
 AvatarKit 的基礎。處理 AvatarKit 的設定與初始化。
 */
@interface AvatarKit : NSObject

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
/**
 Returns the shared singleton AvatarKit instance.
 
 回傳 AvatarKit 共用的單一實例。
 */
@property(class, readonly, nonnull, strong) AvatarKit *sharedInstance NS_SWIFT_NAME(shared);
#endif

/**
 Project version string for AvatarKit.
 
 AvatarKit 當前的版號。
 */
@property(nonatomic, readonly, nonnull) NSString *version;

/**
 The AvatarKit API Key for this app.
 
 回傳目前使用的 API 金鑰。
 */
@property(nonatomic, strong, readonly, nullable) NSString *APIKey;

/**
 Unavailable. Use `+sharedInstance` to retrieve the shared AvatarKit instance.
 
 不可用。請改用 `+sharedInstance` 以取得 AvatarKit 的實例。
 */
- (nonnull instancetype)init __unavailable;

/**
 The recommended way to install AvatarKit into your APP is to place a call to `+startWithAPIKey:` in your `-application:didFinishLaunchingWithOptions:` method.
 
 使用 AvatarKit 前請在你的應用的 `-application:didFinishLaunchingWithOptions:` 內呼叫 `+startWithAPIKey:` ，
 以啟動 AvatarKit。
 
 @param apiKey
 The AvatarKit API Key for this app.
 此應用所使用的 AvatarKit 的 API 金鑰。
 */
+ (void)startWithAPIKey:(nonnull NSString *)apiKey;

/**
 The recommended way to install beta of AvatarKit into your APP is to place a call to `+startWithAPIKey:onBetaServer:` in your `-application:didFinishLaunchingWithOptions:` method.
 
 使用 beta 版的 AvatarKit 前請在你的應用的 `-application:didFinishLaunchingWithOptions:` 內呼叫 `+startWithAPIKey:onBetaServer:` ，
 並指定 `betaMode` 為 `true`，
 以啟動 AvatarKit。
 
 @param apiKey
 The AvatarKit API Key for this app.
 此應用所使用的 AvatarKit 的 API 金鑰。
 
 @param betaMode
 The AvatarKit use beta version on server.
 是否要啟用 beta 版的 AvatarKit 伺服器。
 */
+ (void)startWithAPIKey:(nonnull NSString *)apiKey onBetaServer:(BOOL)betaMode;

@end
