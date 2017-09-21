//
//  DataStructure.h
//  HeadGeniOS
//
//  Created by DboyLiao on 30/03/2017.
//  Copyright © 2017 spe3d. All rights reserved.
//

#ifndef __SPE3D_DATASTRUCTURE_H
#define __SPE3D_DATASTRUCTURE_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <SceneKit/SceneKit.h>

@interface SPTriangleFace : NSObject

@property(nonatomic) int vertexIndex1;
@property(nonatomic) int vertexIndex2;
@property(nonatomic) int vertexIndex3;

- (instancetype)initWithVertexIndex1:(int)index1
                        vertexIndex2:(int)index2
                        vertexIndex3:(int)index3;

@end

@interface SPHeadModel : NSObject

@property NSArray<NSValue *>* vertices;
@property NSArray<NSValue *>* normals;
@property NSArray<NSValue *>* uvs;
@property NSArray<SPTriangleFace*>* meshs;
@property UIImage* faceTexture;
@property UIImage* bodyTexture;

- (instancetype)initWithVertices:(NSArray<NSValue *>*)vertices
                         normals:(NSArray<NSValue *>*)normals
                             uvs:(NSArray<NSValue *>*)uvs
                           meshs:(NSArray<SPTriangleFace*>*)meshs
                     faceTexture:(UIImage*)faceTexture
                     bodyTexture:(UIImage*)bodyTexture;

-(BOOL) saveAsWavefrontObjToDirectory:(NSString*) dirPath
                              objName:(NSString*) objName;
@end

#endif /* __SPE3D_DATASTRUCTURE_H */
