# AvatarKit
[![Build Status](http://internal.spe3d.co:4000/buildStatus/icon?job=AvatarKit-Release-Final)](http://internal.spe3d.co:4000/job/AvatarKit-Release-Final)
[![Documentation](docs/badge.svg)](http://www.spe3d.co/AvatarKit/)
[![CocoaPods](https://img.shields.io/cocoapods/v/AvatarKit.svg)](http://cocoapods.org/?q=AvatarKit)
[![CocoaPods](https://img.shields.io/cocoapods/p/AvatarKit.svg)](https://github.com/spe3d/AvatarKit)

AvatarKit is built in the form of framework, that uses the SceneKit.
AvatarKit framework is built as an universal framework, that means you can use the same binary on both the simulator and device.
AvatarKit is the core technology to generate the a 3D avatar from one single front face photo.
The main features of AvatarKit include:

* Create 3D avatar from one single front face photo
* Render the 3D avatar in the iOS device
* Avatar management
* Assets (accessories management)

## Adding AvatarKit to your project

### Cocoapods

[CocoaPods](http://cocoapods.org) is a dependency manager for Swift and Objective-C Cocoa projects, which automates and simplifies the process of using 3rd-party libraries in your projects.
It is the recommended way to add AvatarKit to your project.

1. Add a pod entry for AvatarKit to your Podfile `pod 'AvatarKit'`
2. Install the pod(s) by running `pod install`, before maybe you need to run `pod repo update`.
3. Include AvatarKit wherever you need it with `import AvatarKit`.
