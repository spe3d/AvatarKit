//
//  DataStructure.h
//  HeadGeniOS
//
//  Created by DboyLiao on 30/03/2017.
//  Copyright © 2017 spe3d. All rights reserved.
//

#ifndef __SPE3D_DATASTRUCTURE_H
#define __SPE3D_DATASTRUCTURE_H

#import <UIKit/UIKit.h>

@interface SPPoint3 : NSObject

@property(nonatomic) CGFloat x;
@property(nonatomic) CGFloat y;
@property(nonatomic) CGFloat z;

-(instancetype) initWith:(CGFloat) x
                       y:(CGFloat) y
                       z:(CGFloat) z;

@end

@interface SPPoint2 : NSObject

@property(nonatomic) CGFloat x;
@property(nonatomic) CGFloat y;

-(instancetype) initWith:(CGFloat) x
                       y:(CGFloat) y;

@end

@interface SPTriangleFace : NSObject

@property(nonatomic) int vertexIndex1;
@property(nonatomic) int vertexIndex2;
@property(nonatomic) int vertexIndex3;

-(instancetype) initWithIndices:(int)index1
                    verteIndex2:(int)index2
                   vertexIndex3:(int)index3;

@end

@interface SPHeadModel : NSObject

@property NSArray<SPPoint3*>* vertices;
@property NSArray<SPPoint3*>* normals;
@property NSArray<SPPoint2*>* uvs;
@property NSArray<SPTriangleFace*>* meshs;
@property UIImage* faceTexture;
@property UIImage* bodyTexture;

-(instancetype) initWithVertices:(NSArray<SPPoint3*>*)vertices
                         normals:(NSArray<SPPoint3*>*)normals
                             uvs:(NSArray<SPPoint2*>*)uvs
                           meshs:(NSArray<SPTriangleFace*>*)meshs
                     faceTexture:(UIImage*)faceTexture
                     bodyTexture:(UIImage*)bodyTexture;

-(BOOL) saveAsWavefrontObjToDirectory:(NSString*) dirPath
                              objName:(NSString*) objName;
@end

#endif /* __SPE3D_DATASTRUCTURE_H */
